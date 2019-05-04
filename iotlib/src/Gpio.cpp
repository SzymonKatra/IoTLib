#include "iotlib/Gpio.hpp"

#include "iotlib/Platform/PlatformGpio.hpp>


namespace iotlib {

    void Gpio::setup(GpioPinDefinition pin, Gpio::Direction direction) {
        switch (direction) {
            case Gpio::Direction::Input: platform::gpioSetupIn(pin); break;
            case Gpio::Direction::Output: platform::gpioSetupOut(pin); break;
        }
    }

    void Gpio::write(GpioPinDefinition pin, bool value) {
        if (value) {
            platform::gpioWriteHigh(pin);
        } else {
            platform::gpioWriteLow(pin);
        }
    }

    bool Gpio::read(GpioPinDefinition pin) {
        return platform::gpioRead(pin);
    }
}