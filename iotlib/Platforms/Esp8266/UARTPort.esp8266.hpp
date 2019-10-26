#pragma once

#include <stdint.h>
#include "Definitions.esp8266.hpp"
#include <driver/uart.h>

namespace iotlib {
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
        iotlib::UARTPortDefinition port;
        bool isUART0Swapped;

    public:
        UARTPort(iotlib::UARTPortDefinition uartPort, uint32_t baudRate, UARTPort::Parity parity, UARTPort::StopBits stopBits);
        ~UARTPort();

        size_t write(const uint8_t* buffer, size_t size);
        size_t read(uint8_t* buffer, size_t size);

        void print(const char* str);

    private:
        uart_parity_t convertParity(UARTPort::Parity parity);
        uart_stop_bits_t convertStopBits(UARTPort::StopBits stopBits);
    };
}