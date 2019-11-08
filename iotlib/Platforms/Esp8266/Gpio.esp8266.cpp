#include <driver/gpio.h>
#include "Gpio.esp8266.hpp"

namespace iotlib
{
    void Gpio::setup(iotlib::GpioPinDefinition pin, iotlib::Gpio::Direction direction)
    {
        gpio_config_t io_conf;
        io_conf.intr_type = GPIO_INTR_DISABLE;
        io_conf.mode = Gpio::convertDirection(direction);
        io_conf.pin_bit_mask = (1 << pin);
        io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
        io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
        gpio_config(&io_conf);
    }

    void Gpio::write(iotlib::GpioPinDefinition pin, bool value)
    {
        gpio_set_level(pin, value);
    }

    bool Gpio::read(GpioPinDefinition pin)
    {
        return gpio_get_level(pin) > 0;
    }

    gpio_mode_t Gpio::convertDirection(Gpio::Direction direction)
    {
        switch (direction)
        {
        case Gpio::Direction::Input: return GPIO_MODE_INPUT;
        case Gpio::Direction::Output: return GPIO_MODE_OUTPUT;
        case Gpio::Direction::OutputOpenDrain: return GPIO_MODE_OUTPUT_OD;
        default: return GPIO_MODE_INPUT;
        }
    }
}