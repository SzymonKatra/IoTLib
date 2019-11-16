#include <driver/gpio.h>
#include "Gpio.esp8266.hpp"

namespace iotlib
{
    Gpio::Gpio(iotlib::GpioPinDefinition pin, iotlib::Gpio::Direction direction)
        : Gpio(pin, direction, false)
    {
    }

    Gpio::Gpio(iotlib::GpioPinDefinition pin, iotlib::Gpio::Direction direction, bool initValue)
        : pin(pin)
    {
        if (pin == esp8266::GPIO_NONE) return;
        
        this->write(initValue);

        gpio_config_t io_conf;
        io_conf.intr_type = GPIO_INTR_DISABLE;
        io_conf.mode = Gpio::convertDirection(direction);
        io_conf.pin_bit_mask = (1 << pin);
        io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
        io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
        gpio_config(&io_conf);
    }

    Gpio::~Gpio()
    {
    }

    void Gpio::write(bool value)
    {
        gpio_set_level(this->pin, value);
    }

    bool Gpio::read()
    {
        return gpio_get_level(this->pin) > 0;
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

    Gpio Gpio::createDummy()
    {
        return Gpio(esp8266::GPIO_NONE, iotlib::Gpio::Direction::Input);
    }
}