#include <iotlib/IoTLib.hpp>
#include <iotlib/OneWireBus.hpp>
#include <iotlib/Devices/DS18B20.hpp>
#include <iotlib/Devices/BME280.hpp>
#include <iostream>

iotlib::Library libGlobal;

int main()
{
    //iotlib::UARTPort uart(iotlib::rpi::UART_Primary, 9600, iotlib::UARTPort::Parity::None, iotlib::UARTPort::StopBits::One);
    //std::cout << "uart created" << std::endl;
    //uart.print("test");
    /*iotlib::Gpio gpio(iotlib::rpi::GPIO4, iotlib::Gpio::Direction::Output, false);
    gpio.write(true);
    iotlib::System::waitUs(5);
    gpio.write(false);
    iotlib::System::waitUs(10);
    gpio.write(true);
    iotlib::System::waitUs(15);
    gpio.write(false);
    iotlib::System::waitUs(20);
    gpio.write(true);
    iotlib::System::waitUs(100);
    gpio.write(false);*/
    
    iotlib::I2CBus i2c(iotlib::rpi::I2C_Bus0, iotlib::rpi::I2C_SDA_GPIO2, iotlib::rpi::I2C_SCL_GPIO3);
    iotlib::BME280 bme(i2c);
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
