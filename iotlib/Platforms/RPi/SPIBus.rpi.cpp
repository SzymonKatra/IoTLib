#include "SPIBus.rpi.hpp"

#include <string.h>
#include <stdlib.h>

namespace iotlib
{
    SPIBus::SPIBus(SPIBusDefinition bus)
        : bus(bus)
    {
        // TODO
    }

    SPIBus::~SPIBus()
    {
        // TODO
    }

    void SPIBus::write(const uint8_t* data, size_t length)
    {
        // TODO
        
    }
    void SPIBus::read(uint8_t* data, size_t length)
    {
        // TODO
    }
}