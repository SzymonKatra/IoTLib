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

    void SPIBus::write(const uint8_t* data, size_t len)
    {
        size_t u32Len = len / 4;
        if (len % 4) u32Len++;
        size_t tlen = u32Len * 4;
        uint8_t* buff = (uint8_t*)malloc(tlen);
        memcpy(buff, data, len);
        if (tlen - len > 0)
        {
            memset(buff + len, 0, tlen - len);
        }

        spi_trans_t trans = {};
        trans.mosi = (uint32_t*)buff;
        trans.bits.mosi = len * 8;
        esp_err_t e = spi_trans(this->bus, trans);
        ESP_LOGI("Spi", "write = %d", e);

        free(buff);

        //while (len)
        //{
        //    uint32_t buf = (*data) << 24;
        //    data++;
        //    len--;

        //    spi_trans_t trans = {};
        //    trans.mosi = &buf;
        //    trans.bits.mosi = 8;
        //    esp_err_t e = spi_trans(this->bus, trans);
        //    ESP_LOGI("Spi", "write = %d", e);
        //    /*uint16_t cmd = SPI_MASTER_WRITE_DATA_TO_SLAVE_CMD;
        //    uint32_t addr = 0;
        //    trans.cmd = &cmd;
        //    trans.addr = &addr;
        //    trans.mosi = (uint32_t*)data;
        //    trans.bits.cmd = 8 * 1;
        //    trans.bits.addr = 0;
        //    trans.bits.mosi = len * 8;
        //    trans.bits.miso = 0;*/

        //    //spi_trans(this->bus, trans);
        //}
        
    }
    void SPIBus::read(uint8_t* data, size_t len)
    {
        size_t u32Len = len / 4;
        if (len % 4) u32Len++;
        size_t tlen = u32Len * 4;
        uint8_t* buff = (uint8_t*)malloc(tlen);

        spi_trans_t trans = {};
        trans.miso = (uint32_t*)buff;
        trans.bits.miso = len * 8;
        esp_err_t e = spi_trans(this->bus, trans);
        ESP_LOGI("Spi", "read = %d", e);
        memcpy(data, buff, len);

        free(buff);

        /*while (len)
        {
            uint32_t buf;

            spi_trans_t trans = {};
            trans.miso = &buf;
            trans.bits.miso = 8;
            esp_err_t e = spi_trans(this->bus, trans);
            ESP_LOGI("Spi", "read = %d", e);

            *data = (uint8_t)(buf >> 24);
            data++;
            len--;
        }*/

        /*spi_trans_t trans;
        uint16_t cmd = SPI_MASTER_READ_DATA_FROM_SLAVE_CMD;
        uint32_t addr = 0;
        trans.cmd = &cmd;
        trans.addr = &addr;
        trans.miso = (uint32_t*)data;
        trans.bits.cmd = 8 * 1;
        trans.bits.addr = 0;
        trans.bits.mosi = 0;
        trans.bits.miso = len * 8;
        
        spi_trans(this->bus, trans);*/
    }
}