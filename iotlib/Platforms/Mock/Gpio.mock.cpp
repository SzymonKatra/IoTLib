#include <iostream>
#include "Definitions.mock.hpp"
#include "../../Gpio.hpp"

namespace iotlib
{
    void Gpio::setup(iotlib::GpioPinDefinition pin, iotlib::Gpio::Direction direction)
    {
        std::cout << "GPIO SETUP pin=" << pin << " direction=" << (int)direction << std::endl;
    }

    void Gpio::write(iotlib::GpioPinDefinition pin, bool value)
    {
        std::cout << "GPIO WRITE pin=" << pin << " value=" << value << std::endl;
    }

    bool Gpio::read(GpioPinDefinition pin)
    {
        std::cout << "GPIO READ " << pin << std::endl;
        return true;
    }
}