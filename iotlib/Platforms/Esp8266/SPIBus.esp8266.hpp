#pragma once

#include <stdint.h>
#include <driver/spi.h>

namespace iotlib
{
    namespace esp8266
    {
        typedef spi_host_t SPIBusDefinition;
        // const SpiBusDefinition CSPI = CSPI_HOST; // used by flash
        const SPIBusDefinition SPI_BusHSPI = HSPI_HOST;
    }

    typedef esp8266::SPIBusDefinition SPIBusDefinition;

    class SPIBus
    {
    private:
        SPIBusDefinition bus;

    public:
        SPIBus(SPIBusDefinition bus);
        ~SPIBus();

        void write(const uint8_t* data, size_t len);
        void read(uint8_t* data, size_t len);
    };
}