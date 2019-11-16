#include <string>
#include <fstream>
#include "Gpio.rpi.hpp"
#include "bcm2835.h"

namespace iotlib
{
    Gpio::Gpio(iotlib::GpioPinDefinition pin, iotlib::Gpio::Direction direction)
        : Gpio(pin, direction, false)
    {
    }

    Gpio::Gpio(iotlib::GpioPinDefinition pin, iotlib::Gpio::Direction direction, bool initValue)
        : pin(pin), direction(direction)
    {
        if (direction == Direction::OutputOpenDrain)
        {
            bcm2835_gpio_clr(this->pin);
            if (initValue)
            {
                bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
            }
            else
            {
                bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
            }
        }
        else
        {
            this->write(initValue);
            bcm2835_gpio_fsel(pin, this->convertDirection(direction));
        }
    }

    Gpio::~Gpio()
    {
    }

    void Gpio::write(bool value)
    {
        if (this->direction == Direction::OutputOpenDrain)
        {
            if (value)
            {
                bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
            }
            else
            {
                bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
            }
        }
        else
        {
            bcm2835_gpio_write(this->pin, value);
        }
    }

    bool Gpio::read()
    {
        return bcm2835_gpio_lev(this->pin);
    }

    bcm2835FunctionSelect Gpio::convertDirection(Direction direction)
    {
        switch (direction)
        {
        case Direction::Input: return BCM2835_GPIO_FSEL_INPT;
        case Direction::Output:
        case Direction::OutputOpenDrain:
            return BCM2835_GPIO_FSEL_OUTP;
        }
    }


    Gpio Gpio::createDummy()
    {
        return Gpio(rpi::GPIO_NONE, iotlib::Gpio::Direction::Input);
    }
}