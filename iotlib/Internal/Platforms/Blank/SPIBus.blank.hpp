#pragma once

#include <stdint.h>

namespace iotlib
{
    namespace blank
    {
        typedef int SPIBusDefinition;
    }

    typedef blank::SPIBusDefinition SPIBusDefinition;

    class SPIBus
    {
    public:
        SPIBus(SPIBusDefinition bus);
        ~SPIBus();

        void write(const uint8_t* data, size_t length);
        void read(uint8_t* data, size_t length);
    };
}