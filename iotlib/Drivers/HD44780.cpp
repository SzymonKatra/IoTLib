#include "HD44780.hpp"

namespace iotlib
{
    const uint8_t PIN_MASK_RS = (1 << 0);
    const uint8_t PIN_MASK_RW = (1 << 1);
    const uint8_t PIN_MASK_E = (1 << 2);
    const uint8_t PIN_MASK_BACKLIGHT = (1 << 3);
    const uint8_t PIN_MASK_D4 = (1 << 4);
    const uint8_t PIN_MASK_D5 = (1 << 5);
    const uint8_t PIN_MASK_D6 = (1 << 6);
    const uint8_t PIN_MASK_D7 = (1 << 7);
    const uint8_t PIN_MASK_D_ALL = PIN_MASK_D4 | PIN_MASK_D5 | PIN_MASK_D6 | PIN_MASK_D7;

    const uint8_t MODE_4_BIT_NIBBLE = 0x03;
    const uint8_t MODE_4_BIT_INIT = 0x02;
    const uint8_t HD44780_CLEAR = (1 << 0);

    const uint8_t HD44780_HOME = (1 << 1);

    const uint8_t CMD_ENTRY_MODE = (1 << 2);
    const uint8_t CMD_ENTRY_MODE_DECREMENT = 0;
    const uint8_t CMD_ENTRY_MODE_INCREMENT = (1 << 1);
    const uint8_t CMD_ENTRY_MODE_SHIFT_CURSOR = 0;
    const uint8_t CMD_ENTRY_MODE_SHIFT_DISPLAY = (1 << 0);

    const uint8_t CMD_DISPLAY_CONTROL = (1 << 3);
    const uint8_t CMD_DISPLAY_CONTROL_ON = (1 << 2);
    const uint8_t CMD_DISPLAY_CONTROL_CURSOR_ON = (1 << 1);
    const uint8_t CMD_DISPLAY_CONTROL_CURSOR_BLINK = (1 << 0);

    const uint8_t CMD_FUNCTION_SET = (1 << 5);
    const uint8_t CMD_FUNCTION_SET_8_BIT = (1 << 4);
    const uint8_t CMD_FUNCTION_SET_4_BIT = 0;
    const uint8_t CMD_FUNCTION_SET_1_LINE = 0;
    const uint8_t CMD_FUNCTION_SET_2_LINE = (1 << 3);
    const uint8_t CMD_FUNCTION_SET_FONT5x7 = 0;
    const uint8_t CMD_FUNCTION_SET_FONT5x10 = (1 << 2);

    const uint8_t CMD_SET_CGRAM = (1 << 6);
    const uint8_t CMD_SET_DDRAM = (1 << 7);

    HD44780::HD44780(Device& device)
        : device(device), pinsState(0)
    {
        this->setBacklight(true);

        this->initSequence();

        this->command(CMD_FUNCTION_SET | CMD_FUNCTION_SET_FONT5x7 | CMD_FUNCTION_SET_2_LINE | CMD_FUNCTION_SET_4_BIT);
        this->displayControl(false, false, false);
        this->clear();
        this->command(CMD_ENTRY_MODE | CMD_ENTRY_MODE_SHIFT_CURSOR | CMD_ENTRY_MODE_INCREMENT);
        this->displayControl(true, false, false);
    }

    HD44780::~HD44780()
    {
    }

    void HD44780::command(uint8_t command)
    {
        this->send(command, false);
    }

    void HD44780::data(uint8_t data)
    {
        this->send(data, true);
    }

    void HD44780::displayControl(bool displayEnabled, bool cursorEnabled, bool blinkingEnabled)
    {
        uint8_t cmd = CMD_DISPLAY_CONTROL;
        if (displayEnabled) cmd |= CMD_DISPLAY_CONTROL_ON;
        if (cursorEnabled) cmd |= CMD_DISPLAY_CONTROL_CURSOR_ON;
        if (blinkingEnabled) cmd |= CMD_DISPLAY_CONTROL_CURSOR_BLINK;
        this->command(cmd);
    }

    void HD44780::clear()
    {
        this->command(HD44780_CLEAR);
        System::waitUs(2000);
    }

    void HD44780::cursorHome()
    {
        this->command(HD44780_HOME);
        System::waitUs(2000);
    }

    void HD44780::cursorGoTo(uint8_t x, uint8_t y)
    {
        this->command(CMD_SET_DDRAM | (x + 0x40 * y));
    }

    void HD44780::defineChar(uint8_t id, const uint8_t data[8])
    {
        this->command(CMD_SET_CGRAM + 8 * id);
        for (size_t i = 0; i < 8; i++) this->data(data[i]);
    }

    void HD44780::text(const char * text)
    {
        while (*text) this->data(*text++);
    }

    void HD44780::send(uint8_t data, bool rs)
    {
        this->setRs(rs);
        this->setRw(false);

        System::waitUs(1);

        this->setE(true);
        this->applyPinsState();

        this->setNibble(data >> 4);
        this->applyPinsState();

        System::waitUs(1);

        this->setE(false);
        this->applyPinsState();

        System::waitUs(1);

        this->setE(true);
        this->applyPinsState();

        this->setNibble(data);
        this->applyPinsState();

        System::waitUs(1);

        this->setE(false);
        this->applyPinsState();

        System::waitUs(50);
    }

    void HD44780::setRs(bool rs)
    {
        if (rs) this->pinsState |= PIN_MASK_RS; else this->pinsState &= ~PIN_MASK_RS;
    }

    void HD44780::setRw(bool rw)
    {
        if (rw) this->pinsState |= PIN_MASK_RW; else this->pinsState &= ~PIN_MASK_RW;
    }

    void HD44780::setE(bool e)
    {
        if (e) this->pinsState |= PIN_MASK_E; else this->pinsState &= ~PIN_MASK_E;
    }

    void HD44780::setBacklight(bool backlight)
    {
        if (backlight) this->pinsState |= PIN_MASK_BACKLIGHT; else this->pinsState &= ~PIN_MASK_BACKLIGHT;
    }

    void HD44780::setNibble(uint8_t nibble)
    {
        this->pinsState &= ~PIN_MASK_D_ALL;

        if (nibble & (1 << 0)) this->pinsState |= PIN_MASK_D4;
        if (nibble & (1 << 1)) this->pinsState |= PIN_MASK_D5;
        if (nibble & (1 << 2)) this->pinsState |= PIN_MASK_D6;
        if (nibble & (1 << 3)) this->pinsState |= PIN_MASK_D7;
    }

    void HD44780::applyPinsState()
    {
        device.write(this->pinsState);
    }
    void HD44780::initSequence()
    {
        this->setE(true);
        this->applyPinsState();

        this->setNibble(MODE_4_BIT_NIBBLE);
        this->applyPinsState();

        this->setE(false);
        this->applyPinsState();

        System::waitUs(5000);

        this->setE(true);
        this->applyPinsState();

        this->setNibble(MODE_4_BIT_NIBBLE);
        this->applyPinsState();

        this->setE(false);
        this->applyPinsState();

        System::waitUs(160);

        this->setE(true);
        this->applyPinsState();

        this->setNibble(MODE_4_BIT_NIBBLE);
        this->applyPinsState();

        this->setE(false);
        this->applyPinsState();

        System::waitUs(160);

        this->setE(true);
        this->applyPinsState();

        this->setNibble(MODE_4_BIT_INIT);
        this->applyPinsState();

        this->setE(false);
        this->applyPinsState();

        System::waitUs(1000);
    }
}