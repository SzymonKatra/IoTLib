#include "IotLib_Config.hpp"
#include <iotlib/IoTLib.hpp>

int main()
{
    iotlib::Gpio::setup(app::LedA, iotlib::Gpio::Direction::Output);
    iotlib::Gpio::write(app::LedA, true);

    return 0;
}