#include "IotLib_Config.hpp"
#include <iotlib/IoTLib.hpp>
#include <iostream>
#include <iotlib/Devices/BME280.hpp>
#include <iotlib/System.hpp>

iotlib::I2CBus* bus;

int main()
{
    //iotlib::Gpio::setup(app::LedA, iotlib::Gpio::Direction::Output);
    //iotlib::Gpio::write(app::LedA, false);
    
    bus = new iotlib::I2CBus(iotlib::rpi::I2C_Bus1, iotlib::rpi::I2C_SDA_GPIO2, iotlib::rpi::I2C_SCL_GPIO3);
    iotlib::BME280* bme280 = new iotlib::BME280(*bus);

    while (1)
    {
        iotlib::BME280::Result data;
        bme280->getData(data);

        std::cout << "bme temp hum press: " << data.Temperature << " " << data.Humidity << " " << data.Pressure << std::endl;
        iotlib::System::sleep(2000);
    }

    return 0;
}
