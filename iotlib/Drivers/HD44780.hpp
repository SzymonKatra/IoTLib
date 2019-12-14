#include "../System.hpp"
#include "../Device.hpp"

namespace iotlib
{
    class HD44780
    {
    private:
        Device& device;
        uint8_t pinsState;

    public:
        HD44780(Device& device);
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