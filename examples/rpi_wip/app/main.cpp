#include <iotlib/IoTLib.hpp>
#include <iotlib/OneWireBus.hpp>
#include <iotlib/Devices/DS18B20.hpp>
#include <iotlib/Devices/BME280.hpp>
#include <iostream>

iotlib::Library libGlobal;

int main()
{
    iotlib::SPIBus spi(iotlib::rpi::SPI_Bus0);
    //uint8_t arr[] = { 0xAA, 0xBB, 0xCC };
    //spi.write(arr, 3);

    //iotlib::I2CBus i2c(iotlib::rpi::I2C_Bus0, iotlib::rpi::I2C_SDA_GPIO2, iotlib::rpi::I2C_SCL_GPIO3);
    //iotlib::BME280 bme(i2c);
    iotlib::BME280 bme(spi, iotlib::rpi::GPIO21);
    iotlib::System::sleep(2000);
    iotlib::BME280::Result res;
    bme.getData(res);
    std::cout << res.Temperature << std::endl;

    iotlib::OneWireBus oneWire(iotlib::rpi::GPIO4);
    oneWire.searchBegin(iotlib::OneWireBus::SearchType::SearchRom);
    iotlib::OneWireBus::Address addr = oneWire.searchNext();
    iotlib::DS18B20 temp(oneWire, addr);
    temp.startConversion();
    iotlib::System::sleep(2000);
    int16_t result = temp.readRawTemperature();
    std::cout << (result >> 4) << std::endl;

    return 0;
}
