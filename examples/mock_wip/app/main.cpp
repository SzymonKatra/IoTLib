#include "IotLib_Config.hpp"
#include <iotlib/IoTLib.hpp>

int main()
{
    iotlib::Gpio::setup(app::LedA, iotlib::Gpio::Direction::Out);

    return 0;
}