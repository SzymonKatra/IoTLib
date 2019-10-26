#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_system.h"
#include <esp_log.h>
#include "IotLib_Config.hpp"
#include <iotlib/IoTLib.hpp>
#include <string.h>
#include <iotlib/bosch/bme280.h>

iotlib::I2CBus* bus;

void user_delay_ms(uint32_t period)
{
    vTaskDelay(period / portTICK_PERIOD_MS);
}

int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
    bus->write(dev_id, &reg_addr, 1);
    bus->read(dev_id, reg_data, len);
    /*
     * The parameter dev_id can be used as a variable to store the I2C address of the device
     */

     /*
      * Data on the bus should be like
      * |------------+---------------------|
      * | I2C action | Data                |
      * |------------+---------------------|
      * | Start      | -                   |
      * | Write      | (reg_addr)          |
      * | Stop       | -                   |
      * | Start      | -                   |
      * | Read       | (reg_data[0])       |
      * | Read       | (....)              |
      * | Read       | (reg_data[len - 1]) |
      * | Stop       | -                   |
      * |------------+---------------------|
      */

    return rslt;
}

int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
    bus->beginWrite(dev_id, true);
    bus->write(&reg_addr, 1);
    bus->write(reg_data, len);
    bus->endWrite();
    /*uint8_t* data = (uint8_t*)malloc(len + 1);
    *data = reg_addr;
    memcpy(data + 1, reg_data, len);
    bus->write(dev_id, data, len + 1);
    free(data);*/
    /*
     * The parameter dev_id can be used as a variable to store the I2C address of the device
     */

     /*
      * Data on the bus should be like
      * |------------+---------------------|
      * | I2C action | Data                |
      * |------------+---------------------|
      * | Start      | -                   |
      * | Write      | (reg_addr)          |
      * | Write      | (reg_data[0])       |
      * | Write      | (....)              |
      * | Write      | (reg_data[len - 1]) |
      * | Stop       | -                   |
      * |------------+---------------------|
      */

    return rslt;
}


extern "C" {
    void app_main(void)
    {
        printf("HELLO ESP SDK version:%s\n", esp_get_idf_version());
        iotlib::Gpio::setup(app::LedA, iotlib::Gpio::Direction::Output);
        iotlib::Gpio::write(app::LedA, false);

        //iotlib::UARTPort serial(app::Debug, 74880, iotlib::UARTPort::Parity::None, iotlib::UARTPort::StopBits::One);

        //serial.print("Hello UART from esp!\n");
        //serial.print("And second line!\n");

        bus = new iotlib::I2CBus(iotlib::esp8266::I2C_Bus0, iotlib::esp8266::I2C_SDA_GPIO4, iotlib::esp8266::I2C_SCL_GPIO5);

        struct bme280_dev dev;
        int8_t rslt = BME280_OK;

        dev.dev_id = BME280_I2C_ADDR_PRIM;
        dev.intf = BME280_I2C_INTF;
        dev.read = user_i2c_read;
        dev.write = user_i2c_write;
        dev.delay_ms = user_delay_ms;

        rslt = bme280_init(&dev);
        ESP_LOGI("main", "bme result: %d", rslt);

        rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, &dev);
        ESP_LOGI("main", "bme set result: %d", rslt);

        while (1)
        {
            bme280_data data;
            bme280_get_sensor_data(BME280_ALL, &data, &dev);

            ESP_LOGI("main", "bme temp hum press: %d %d %d", data.temperature, data.humidity, data.pressure);
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }
    }
}

