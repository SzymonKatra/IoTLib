#pragma once

#include <stdint.h>
#include <driver/uart.h>

namespace iotlib
{
    namespace esp8266
    {
        typedef uart_port_t UARTPortDefinition;
        const UARTPortDefinition UART_Port0 = UART_NUM_0;
        const UARTPortDefinition UART_Port0Swapped = (UARTPortDefinition)(UART_NUM_0 + UART_NUM_MAX);
        const UARTPortDefinition UART_Port1 = UART_NUM_1;
    }

    typedef esp8266::UARTPortDefinition UARTPortDefinition;

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
            OneAndHalf,
            Two
        };

    private:
        UARTPortDefinition port;
        bool isUART0Swapped;

    public:
        UARTPort(UARTPortDefinition uartPort, uint32_t baudRate, UARTPort::Parity parity, UARTPort::StopBits stopBits);
        ~UARTPort();

        size_t write(const uint8_t* buffer, size_t size);
        size_t read(uint8_t* buffer, size_t size);

        void print(const char* str);

    private:
        uart_parity_t convertParity(UARTPort::Parity parity);
        uart_stop_bits_t convertStopBits(UARTPort::StopBits stopBits);
    };
}