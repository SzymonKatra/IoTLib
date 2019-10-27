#include <string>
#include <fstream>
#include "Gpio.rpi.hpp"

namespace iotlib
{
    void Gpio::setup(GpioPinDefinition pin, Direction direction)
    {
        std::ofstream stream("/sys/class/gpio/gpio" + std::to_string(pin) + "/direction");
        stream << (direction == Direction::Output ? "out" : "in");
        stream.close();
    }

    void Gpio::write(GpioPinDefinition pin, bool value)
    {
        std::ofstream stream("/sys/class/gpio/gpio" + std::to_string(pin) + "/value");
        stream << (value ? "1" : "0");
        stream.close();
    }

    bool Gpio::read(GpioPinDefinition pin)
    {
        std::string val;
        std::ifstream stream("/sys/class/gpio/gpio" + std::to_string(pin) + "/value");
        stream >> val;
        return val == "1";
    }
}