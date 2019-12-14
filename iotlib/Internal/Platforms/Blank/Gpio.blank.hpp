#pragma once

namespace iotlib
{
    namespace blank
    {
        typedef int GpioPinDefinition;
        const GpioPinDefinition GPIO_NONE = 0x7FFFFFFF;
    }

    typedef blank::GpioPinDefinition GpioPinDefinition;

    class Gpio
    {
    public:
        enum class Direction {
            Input,
            Output,
            OutputOpenDrain
        };

    public:
        Gpio(iotlib::GpioPinDefinition, iotlib::Gpio::Direction direction);
        Gpio(iotlib::GpioPinDefinition, iotlib::Gpio::Direction direction, bool initValue);
        ~Gpio();

        void write(bool value);
        bool read();

        static Gpio createDummy();
    };
}
