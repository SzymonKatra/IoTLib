#include <iotlib/IoTLib.hpp>
#include <iotlib/OneWireBus.hpp>
#include <iotlib/Devices/DS18B20.hpp>
#include <iotlib/Devices/BME280.hpp>
#include <iostream>
#include <ios>
#include <vector>

iotlib::Library libGlobal;

int main()
{
    iotlib::SPIBus spi(iotlib::rpi::SPI_Bus0);
    iotlib::I2CBus i2c(iotlib::rpi::I2C_Bus0, iotlib::rpi::I2C_SDA_GPIO2, iotlib::rpi::I2C_SCL_GPIO3);
    iotlib::OneWireBus oneWire(iotlib::rpi::GPIO4);

    //iotlib::BME280 bme(i2c);
    iotlib::BME280 bme(spi, iotlib::rpi::GPIO21);

    iotlib::System::sleep(2000);
    iotlib::BME280::Result res;
    bme.getData(res);
    std::cout << res.Temperature << std::endl;

    std::vector<iotlib::DS18B20*> tempSensors;
    oneWire.searchBegin(iotlib::OneWireBus::SearchType::SearchRom);
    iotlib::OneWireBus::Address addr = oneWire.searchNext();
    while (addr != iotlib::OneWireBus::NoDevice)
    {
        std::cout << "dev found" << std::endl;
        tempSensors.push_back(new iotlib::DS18B20(oneWire, addr));
        addr = oneWire.searchNext();
    }

    while (true)
    {
        iotlib::DS18B20::allStartConversion(oneWire);
        iotlib::System::sleep(1000);
        
        for (iotlib::DS18B20* t : tempSensors)
        {
            const iotlib::OneWireBus::Address& addr = t->getAddress();
            int16_t result = t->readRawTemperature();
            std::cout << std::hex << addr.Value << std::dec << ": " << (result >> 4) << std::endl;
        }
    }


    for (iotlib::DS18B20* t : tempSensors)
    {
        delete t;
    }

    return 0;
}
