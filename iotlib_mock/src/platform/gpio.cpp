#include <iotlib/platform/gpio.hpp>

#include <iostream>

namespace iotlib {
    namespace platform {
        void gpio_setup_in(iotlib::GpioPinDefinition pin) {
            std::cout << "GPIO SETUP IN " << pin << std::endl;
        }

        void gpio_setup_out(iotlib::GpioPinDefinition pin) {
            std::cout << "GPIO SETUP OUT " << pin << std::endl;
        }

        void gpio_write_high(iotlib::GpioPinDefinition pin) {
            std::cout << "GPIO WRITE HIGH " << pin << std::endl;
        }

        void gpio_write_low(iotlib::GpioPinDefinition pin) {
            std::cout << "GPIO WRITE LOW " << pin << std::endl;
        }

        bool gpio_read(iotlib::GpioPinDefinition pin) {
            std::cout << "GPIO READ " << pin << std::endl;
            return true;
        }
    }
}