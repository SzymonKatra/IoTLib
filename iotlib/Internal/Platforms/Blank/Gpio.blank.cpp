#include "Gpio.blank.hpp"

namespace iotlib
{
    Gpio::Gpio(iotlib::GpioPinDefinition pin, iotlib::Gpio::Direction direction)
    {
        #warning Not implemented!
    }

    Gpio::Gpio(iotlib::GpioPinDefinition pin, iotlib::Gpio::Direction direction, bool initValue)
    {
        #warning Not implemented!
    }

    Gpio::~Gpio()
    {
        #warning Not implemented!
    }

    void Gpio::write(bool value)
    {
        #warning Not implemented!
    }

    bool Gpio::read()
    {
        #warning Not implemented!
    }

    gpio_mode_t Gpio::convertDirection(Gpio::Direction direction)
    {
        #warning Not implemented!
    }

    Gpio Gpio::createDummy()
    {
        return Gpio(blank::GPIO_NONE, iotlib::Gpio::Direction::Input);
    }
}