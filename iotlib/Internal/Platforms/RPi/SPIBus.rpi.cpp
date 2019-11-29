#include "SPIBus.rpi.hpp"

#include <string.h>
#include <stdlib.h>
#include "bcm2835.h"

namespace iotlib
{
    SPIBus::SPIBus(SPIBusDefinition bus)
        : bus(bus)
    {
        bcm2835_spi_begin();
        bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
        bcm2835_spi_setDataMode(BCM2835_SPI_MODE0); // todo: configure it
    }

    SPIBus::~SPIBus()
    {
        bcm2835_spi_end();
    }

    void SPIBus::write(const uint8_t* data, size_t length)
    {
        bcm2835_spi_writenb((const char*)data, length);
        
    }
    void SPIBus::read(uint8_t* data, size_t length)
    {
        bcm2835_spi_transfern((char*)data, length);
    }
}