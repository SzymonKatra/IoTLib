#include <string>
#include <fstream>

namespace iotlib {
    namespace platform {
        void gpioSetupIn(iotlib::GpioPinDefinition pin) {
            std::ofstream stream("/sys/class/gpio/gpio" + std::to_string(pin) + "/direction");
            stream << "in";
            stream.close();
        }

        void gpioSetupOut(iotlib::GpioPinDefinition pin) {
            std::ofstream stream("/sys/class/gpio/gpio" + std::to_string(pin) + "/direction");
            stream << "out";
            stream.close();
        }

        void gpioWriteHigh(iotlib::GpioPinDefinition pin) {
            std::ofstream stream("/sys/class/gpio/gpio" + std::to_string(pin) + "/value");
            stream << "1";
            stream.close();
        }

        void gpioWriteLow(iotlib::GpioPinDefinition pin) {
            std::ofstream stream("/sys/class/gpio/gpio" + std::to_string(pin) + "/value");
            stream << "0";
            stream.close();
        }

        bool gpioRead(iotlib::GpioPinDefinition pin) {
            std::string val;
            std::ifstream stream("/sys/class/gpio/gpio" + std::to_string(pin) + "/value");
            stream >> val;
            return val == "1";
        }
    }
}