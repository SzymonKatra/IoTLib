#include <driver/i2c.h>
#include "../../I2CBus.hpp"
#include "Definitions.esp8266.hpp"

namespace iotlib
{
    I2CBus::I2CBus(iotlib::I2CBusDefinition bus, iotlib::I2CSdaPinDefinition sdaPin, iotlib::I2CSclPinDefinition sclPin)
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

    void I2CBus::write(uint8_t address, const uint8_t* data, size_t length, bool checkAck)
    {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, address << 1, checkAck);
        i2c_master_write(cmd, (uint8_t*)data, length, checkAck);
        i2c_master_stop(cmd);
        i2c_master_cmd_begin(this->bus, cmd, 0);
        
        i2c_cmd_link_delete(cmd);
    }

    void I2CBus::read(uint8_t address, uint8_t* data, size_t length, bool checkAck)
    {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();

        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (address << 1) | 1, checkAck);
        i2c_master_read(cmd, data, length, I2C_MASTER_LAST_NACK);
        i2c_master_stop(cmd);
        i2c_master_cmd_begin(this->bus, cmd, 0);
        
        i2c_cmd_link_delete(cmd);
    }

    void I2CBus::beginWrite(uint8_t address, bool checkAck)
    {
        this->platformState = i2c_cmd_link_create();

        i2c_master_start(this->platformState);
        i2c_master_write_byte(this->platformState, address << 1, checkAck);
    }

    void I2CBus::write(const uint8_t* data, size_t length)
    {
        i2c_master_write(this->platformState, (uint8_t*), length)
    }

    void I2CBus::endWrite()
    {

    }
}