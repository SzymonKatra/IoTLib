#include <string>
#include <fstream>
#include "Gpio.rpi.hpp"

namespace iotlib
{
    Gpio::Gpio(GpioPinDefinition pin, Direction direction)
        : pin(pin)
    {
        std::ofstream stream("/sys/class/gpio/gpio" + std::to_string(pin) + "/direction");
        stream << (direction == Direction::Output ? "out" : "in");
        stream.close();
    }

    Gpio::~Gpio()
    {
    }

    void Gpio::write(bool value)
    {
        std::ofstream stream("/sys/class/gpio/gpio" + std::to_string(pin) + "/value");
        stream << (value ? "1" : "0");
        stream.close();
    }

    bool Gpio::read()
    {
        std::string val;
        std::ifstream stream("/sys/class/gpio/gpio" + std::to_string(pin) + "/value");
        stream >> val;
        return val == "1";
    }
}