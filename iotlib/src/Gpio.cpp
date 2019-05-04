#include <iotlib/Gpio.hpp>
#include <iotlib/platform/gpio.hpp>


namespace iotlib {

    void Gpio::setup(GpioPinDefinition pin, Gpio::Direction direction) {
        switch (direction)
        {
            case Gpio::Direction::Input: platform::gpio_setup_in(pin); break;
            case Gpio::Direction::Output: platform::gpio_setup_out(pin); break;
        }
    }

    void Gpio::write(GpioPinDefinition pin, bool value) {
        if (value) {
            platform::gpio_write_high(pin);
        } else {
            platform::gpio_write_low(pin);
        }
    }

    bool Gpio::read(GpioPinDefinition pin) {
        return platform::gpio_read(pin);
    }
}