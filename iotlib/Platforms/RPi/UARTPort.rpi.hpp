#pragma once

#include <stdint.h>
#include <stddef.h>
#include <termios.h>

namespace iotlib
{
    namespace rpi
    {
        typedef const char* UARTPortDefinition;
        const UARTPortDefinition UART_Primary = "/dev/serial0";
        const UARTPortDefinition UART_Secondary = "/dev/serial1";
    }

    typedef rpi::UARTPortDefinition UARTPortDefinition;

    class UARTPort
    {
    public:
        enum class Parity
        {
            None,
            Even,
            Odd
        };
        enum class StopBits
        {
            One,
            Two
        };

    private:
        UARTPortDefinition port;
        int fd;

    public:
        UARTPort(UARTPortDefinition uartPort, uint32_t baudRate, UARTPort::Parity parity, UARTPort::StopBits stopBits);
        ~UARTPort();

        size_t write(const uint8_t* buffer, size_t size);
        size_t read(uint8_t* buffer, size_t size);

        void print(const char* str);

    private:
        tcflag_t convertParity(UARTPort::Parity parity);
        tcflag_t convertStopBits(UARTPort::StopBits stopBits);
    };
}