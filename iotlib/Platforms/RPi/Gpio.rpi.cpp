#include <string>
#include <fstream>
#include "../../Gpio.hpp"
#include "Definitions.rpi.hpp"

namespace iotlib
{
    void Gpio::setup(iotlib::GpioPinDefinition pin, iotlib::Gpio::Direction direction)
    {
        std::ofstream stream("/sys/class/gpio/gpio" + std::to_string(pin) + "/direction");
        stream << (direction == iotlib::Gpio::Direction::Output ? "out" : "in");
        stream.close();
    }

    void Gpio::write(iotlib::GpioPinDefinition pin, bool value)
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