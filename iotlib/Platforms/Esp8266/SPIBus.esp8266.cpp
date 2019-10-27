#include "SPIBus.esp8266.hpp"

namespace iotlib
{
    SPIBus::SPIBus(SPIBusDefinition bus)
        : bus(bus)
    {
        spi_config_t config;
        config.clk_div = SPI_5MHz_DIV;
        config.mode = SPI_MASTER_MODE;


        spi_init(this->bus, &config);
    }

    SPIBus::~SPIBus()
    {

    }
}