#pragma once

#include "Definitions.esp8266.hpp"

namespace iotlib
{
    class Gpio
    {
    public:
        enum class Direction {
            Input,
            Output
        };

        static void setup(iotlib::GpioPinDefinition pin, iotlib::Gpio::Direction direction);
        static void write(iotlib::GpioPinDefinition pin, bool value);
        static bool read(iotlib::GpioPinDefinition pin);
    };
}
