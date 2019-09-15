#pragma once

#include "Definitions.hpp"

namespace iotlib {
    class Gpio {
    public:
        enum class Direction {
            Input,
            Output
        };

        static void setup(iotlib::GpioPinDefinition pin, Direction direction);
        static void write(iotlib::GpioPinDefinition pin, bool value);
        static bool read(iotlib::GpioPinDefinition pin);
    };
}
