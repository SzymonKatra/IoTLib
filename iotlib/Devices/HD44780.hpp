#include "../Gpio.hpp"
#include "../System.hpp"
#include "../I2CBus.hpp"

namespace iotlib
{
    class HD44780
    {
    private:
        /*uint8_t rsBit;
        uint8_t rwBit;
        uint8_t eBit;
        uint8_t d4Bit;
        uint8_t d5Bit;
        uint8_t d6Bit;
        uint8_t d7Bit;*/
        I2CBus& i2c;
        uint8_t i2cAddress;
        uint8_t pinsState;

    public:
        HD44780(I2CBus& i2c, uint8_t address);
        ~HD44780();

        void command(uint8_t command);
        void data(uint8_t data);

        void displayControl(bool displayEnabled, bool cursorEnabled, bool blinkingEnabled);

        void clear();

        void cursorHome();
        void cursorGoTo(uint8_t x, uint8_t y);

        void defineChar(uint8_t id, const uint8_t data[8]);

        void text(const char* text);

    private:
        void send(uint8_t data, bool rs);
        void setRs(bool rs);
        void setRw(bool rw);
        void setE(bool e);
        void setBacklight(bool backlight);
        void setNibble(uint8_t nibble);
        void applyPinsState();

        void initSequence();
    };
}