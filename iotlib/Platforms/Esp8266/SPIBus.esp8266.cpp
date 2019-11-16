#include "SPIBus.esp8266.hpp"

#include <esp_log.h>
#include <string.h>
#include <stdlib.h>

namespace iotlib
{
    SPIBus::SPIBus(SPIBusDefinition bus)
        : bus(bus)
    {
        spi_config_t config;
        config.interface.val = SPI_DEFAULT_INTERFACE;
        config.interface.byte_rx_order = SPI_BYTE_ORDER_LSB_FIRST;
        config.interface.byte_tx_order = SPI_BYTE_ORDER_LSB_FIRST;
        config.intr_enable.val = SPI_MASTER_DEFAULT_INTR_ENABLE;
        config.mode = SPI_MASTER_MODE;
        config.clk_div = SPI_5MHz_DIV;
        config.event_cb = NULL;

        spi_init(this->bus, &config);
    }

    SPIBus::~SPIBus()
    {
        spi_deinit(this->bus);
    }

    void SPIBus::write(const uint8_t* data, size_t length)
    {
        uint32_t* buffer = NULL;

        if (length % 4)
        {
            size_t u32Count = (length / 4) + 1;
            size_t totalLength = u32Count * 4;

            buffer = (uint32_t*)malloc(totalLength);
            memcpy(buffer, data, length);
        }

        spi_trans_t trans = {};
        trans.mosi = buffer != NULL ? buffer : (uint32_t*)data;
        trans.bits.mosi = length * 8;

        spi_trans(this->bus, trans);

        if (buffer != NULL)
        {
            free(buffer);
        }
        
    }
    void SPIBus::read(uint8_t* data, size_t length)
    {
        uint32_t* buffer = NULL;

        if (length % 4)
        {
            size_t u32Count = (length / 4) + 1;
            size_t totalLength = u32Count * 4;

            buffer = (uint32_t*)malloc(totalLength);
        }

        spi_trans_t trans = {};
        trans.miso = buffer != NULL ? buffer : (uint32_t*)data;
        trans.bits.miso = length * 8;

        spi_trans(this->bus, trans);

        if (buffer != NULL)
        {
            memcpy(data, buffer, length);
            free(buffer);
        }
    }
    }
}