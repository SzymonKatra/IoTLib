#pragma once

#include <iotlib/Platform/PlatformDefinitions.hpp>

namespace iotlib {
    namespace platform {
        void gpioSetupIn(iotlib::GpioPinDefinition pin);
        void gpioSetupOut(iotlib::GpioPinDefinition pin);
        void gpioWriteHigh(iotlib::GpioPinDefinition pin);
        void gpioWriteLow(iotlib::GpioPinDefinition pin);
        bool gpioRead(iotlib::GpioPinDefinition pin);
    }
}