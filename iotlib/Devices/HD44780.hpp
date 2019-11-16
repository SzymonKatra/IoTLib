#include "../Gpio.hpp"
#include "../System.hpp"
#include "../I2CBus.hpp"

namespace iotlib
{
    class HD44780
    {
        HD44780(Gpio& db4Gpio, Gpio& db5Gpio, Gpio& db6Gpio, Gpio& db7Gpio, Gpio& rsGpio, Gpio& eGpio);
        HD44780(I2CBus& i2c, uint8_t address);
        ~HD44780();

        void command(uint8_t command);
        void data(uint8_t data);

        void displayControl(bool displayEnabled, bool cursorEnabled, bool blinkingEnabled);

        void clear();

        void cursorHome();
        void cursorGoTo(uint8_t x, uint8_t y);

        void text(const char* text);
    };
}