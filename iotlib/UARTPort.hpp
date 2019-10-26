#pragma once

#include <stdint.h>
#include "Definitions.hpp"

namespace iotlib {
    class UARTPort
    {
    private:
        UARTPortDefinition port;
        void* platformState;

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

        UARTPort(UARTPortDefinition uartPort, uint32_t baudRate, Parity parity, StopBits stopBits);
        ~UARTPort();

        size_t write(const uint8_t* buffer, size_t size);
        size_t read(uint8_t* buffer, size_t size);

        void print(const char* str);
        void println(const char* str);
    };
}