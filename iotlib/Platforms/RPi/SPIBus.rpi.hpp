#pragma once

#include <stdint.h>
#include <stddef.h>

namespace iotlib
{
    namespace rpi
    {
        typedef int SPIBusDefinition;
    }

    typedef rpi::SPIBusDefinition SPIBusDefinition;

    class SPIBus
    {
    private:
        SPIBusDefinition bus;

    public:
        SPIBus(SPIBusDefinition bus);
        ~SPIBus();

        void write(const uint8_t* data, size_t length);
        void read(uint8_t* data, size_t length);
    };
}