#include <driver/i2c.h>

//void i2cSetup(iotlib::I2CBusDefinition bus, iotlib::I2CSdaPinDefinition sdaPin, iotlib::I2CSclPinDefinition sclPin)
//{
//    i2c_config_t conf;
//    conf.mode = I2C_MODE_MASTER;
//    conf.sda_io_num = sdaPin;
//    conf.sda_pullup_en = GPIO_PULLUP_DISABLE;
//    conf.scl_io_num = sclPin;
//    conf.scl_pullup_en = GPIO_PULLUP_DISABLE;
//
//    i2c_driver_install(bus, conf.mode);
//    i2c_param_config(bus, &conf);
//}
//
//void i2cWrite(iotlib::I2CBusDefinition bus, uint8_t address, const uint8_t* data, size_t length)
//{
//    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//
//    i2c_master_start(cmd);
//    while (length--)
//    {
//        i2c_master_write_byte(cmd, *data, true);
//        data++;
//    }
//    i2c_master_stop(cmd);
//    i2c_master_cmd_begin(bus, cmd, 0);
//
//    i2c_cmd_link_delete(cmd);
//}
//
//void i2cRead(iotlib::I2CBusDefinition bus, uint8_t address uint8_t* data, size_t length)
//{
//    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//    
//    i2c_master_start(cmd);
//    i2c
//    i2c_master_stop(cmd);
//    i2c_master_cmd_begin(bus, cmd, 0);
//
//    i2c_cmd_link_delete(cmd);
//}