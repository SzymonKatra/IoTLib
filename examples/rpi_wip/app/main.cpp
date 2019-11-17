#include <iotlib/UARTPort.hpp>
#include <iotlib/Gpio.hpp>
#include <iotlib/System.hpp>
#include <iotlib/OneWireBus.hpp>
#include <iotlib/Devices/DS18B20.hpp>
#include <iostream>

int main()
{
    iotlib::System::initialize();

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

    iotlib::OneWireBus oneWire(iotlib::rpi::GPIO4);
    oneWire.searchBegin(iotlib::OneWireBus::SearchType::SearchRom);
    iotlib::OneWireBus::Address addr = oneWire.searchNext();
    iotlib::DS18B20 temp(oneWire, addr);
    temp.startConversion();
    iotlib::System::sleep(2000);
    int16_t result = temp.readRawTemperature();
    std::cout << (result >> 4) << std::endl;

    iotlib::System::finalize();

    return 0;
}
