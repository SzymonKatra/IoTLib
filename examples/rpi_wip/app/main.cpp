#include <iotlib/UARTPort.hpp>
#include <iostream>

int main()
{
    iotlib::UARTPort uart(iotlib::rpi::UART_Primary, 9600, iotlib::UARTPort::Parity::None, iotlib::UARTPort::StopBits::One);
    std::cout << "uart created" << std::endl;
    uart.print("test");

    return 0;
}
