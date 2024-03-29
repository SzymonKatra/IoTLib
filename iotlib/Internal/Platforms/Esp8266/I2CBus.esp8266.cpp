#include <driver/i2c.h>
#include "I2CBus.esp8266.hpp"

namespace iotlib
{
    I2CBus::I2CBus(I2CBusDefinition bus, I2CSdaPinDefinition sdaPin, I2CSclPinDefinition sclPin)
    {
        this->bus = bus;

        i2c_config_t conf;
        conf.mode = I2C_MODE_MASTER;
        conf.sda_io_num = sdaPin;
        conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
        conf.scl_io_num = sclPin;
        conf.scl_pullup_en = GPIO_PULLUP_ENABLE;

        i2c_driver_install(this->bus, conf.mode);
        i2c_param_config(this->bus, &conf);
    }
    I2CBus::~I2CBus()
    {
        i2c_driver_delete(this->bus);
    }

    void I2CBus::write(uint8_t address, const uint8_t* data, size_t length)
    {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();

        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, address << 1, true);
        i2c_master_write(cmd, (uint8_t*)data, length, true);
        i2c_master_stop(cmd);
        i2c_master_cmd_begin(this->bus, cmd, 0);

        i2c_cmd_link_delete(cmd);
    }

    void I2CBus::read(uint8_t address, uint8_t* data, size_t length)
    {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();

        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (address << 1) | 1, true);
        i2c_master_read(cmd, data, length, I2C_MASTER_LAST_NACK);
        i2c_master_stop(cmd);
        i2c_master_cmd_begin(this->bus, cmd, 0);

        i2c_cmd_link_delete(cmd);
    }

    void I2CBus::beginWrite(uint8_t address)
    {
        this->currentWriteCmd = i2c_cmd_link_create();

        i2c_master_start(this->currentWriteCmd);
        i2c_master_write_byte(this->currentWriteCmd, address << 1, true);
    }

    void I2CBus::write(const uint8_t* data, size_t length)
    {
        i2c_master_write(this->currentWriteCmd, (uint8_t*)data, length, true);
    }

    void I2CBus::endWrite()
    {
        i2c_master_stop(this->currentWriteCmd);
        i2c_master_cmd_begin(this->bus, this->currentWriteCmd, 0);
        i2c_cmd_link_delete(this->currentWriteCmd);
        this->currentWriteCmd = NULL;
    }

    bool I2CBus::isDevicePresent(uint8_t address)
    {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();

        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, address << 1, true);
        i2c_master_stop(cmd);
        esp_err_t e = i2c_master_cmd_begin(this->bus, cmd, 0);

        i2c_cmd_link_delete(cmd);

        return e == ESP_OK;
    }
}