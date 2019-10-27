#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_system.h"
#include <esp_log.h>
#include "IotLib_Config.hpp"
#include <iotlib/IoTLib.hpp>
#include <string.h>
#include <iotlib/BME280.hpp>

iotlib::I2CBus* bus;

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
        iotlib::BME280* bme280 = new iotlib::BME280(*bus);

        while (1)
        {
            bme280_data data;
            bme280->getData(data);

            ESP_LOGI("main", "bme temp hum press: %d %d %d", data.temperature, data.humidity, data.pressure);
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }
    }
}

