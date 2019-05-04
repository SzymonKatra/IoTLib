#pragma once

#include <iotlib/Platform/PlatformDefinitions.hpp>

namespace iotlib {
    namespace platform {
        void gpio_setup_in(iotlib::GpioPinDefinition pin);
        void gpio_setup_out(iotlib::GpioPinDefinition pin);
        void gpio_write_high(iotlib::GpioPinDefinition pin);
        void gpio_write_low(iotlib::GpioPinDefinition pin);
        bool gpio_read(iotlib::GpioPinDefinition pin);
    }
}