#pragma once

#include <freertos/FreeRTOS.h>
#include <stdint.h>

namespace iotlib
{
    namespace blank
    {
        typedef int UARTPortDefinition;
    }

    typedef blank::UARTPortDefinition UARTPortDefinition;

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

    public:
        UARTPort(UARTPortDefinition uartPort, uint32_t baudRate, UARTPort::Parity parity, UARTPort::StopBits stopBits);
        ~UARTPort();

        size_t write(const uint8_t* buffer, size_t size);
        size_t read(uint8_t* buffer, size_t size);

        void print(const char* str);
    };
}