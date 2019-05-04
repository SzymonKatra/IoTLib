#include <iostream>

namespace iotlib {
    namespace platform {
        void gpioSetupIn(iotlib::GpioPinDefinition pin) {
            std::cout << "GPIO SETUP IN " << pin << std::endl;
        }

        void gpioSetupOut(iotlib::GpioPinDefinition pin) {
            std::cout << "GPIO SETUP OUT " << pin << std::endl;
        }

        void gpioWriteHigh(iotlib::GpioPinDefinition pin) {
            std::cout << "GPIO WRITE HIGH " << pin << std::endl;
        }

        void gpioWriteLow(iotlib::GpioPinDefinition pin) {
            std::cout << "GPIO WRITE LOW " << pin << std::endl;
        }

        bool gpioRead(iotlib::GpioPinDefinition pin) {
            std::cout << "GPIO READ " << pin << std::endl;
            return true;
        }
    }
}