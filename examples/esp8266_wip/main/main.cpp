#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_system.h"
#include <esp_log.h>
#include "IotLib_Config.hpp"
#include <iotlib/IoTLib.hpp>
#include <string.h>
#include <iotlib/Devices/BME280.hpp>
#include <iotlib/Devices/DS18B20.hpp>
#include <sys/time.h>

//iotlib::I2CBus* bus;

int32_t xx_time_get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (int32_t)(tv.tv_sec * 1000000LL + tv.tv_usec);
}

extern "C" {
    void app_main(void)
    {
        printf("HELLO ESP SDK version:%s\n", esp_get_idf_version());
        /*iotlib::Gpio::setup(app::LedA, iotlib::Gpio::Direction::Input);
        iotlib::Gpio::write(app::LedA, false);
        iotlib::System::sleep(1000);
        iotlib::Gpio::setup(app::LedA, iotlib::Gpio::Direction::Output);
        iotlib::System::sleep(1000);
        iotlib::Gpio::setup(app::LedA, iotlib::Gpio::Direction::Input);
        iotlib::System::sleep(1000);*/
        //iotlib::Gpio::setup(app::LedA, iotlib::Gpio::Direction::Output);

        
        iotlib::OneWireBus oneWire(iotlib::esp8266::GPIO4);
        iotlib::DS18B20 tempSensor(oneWire);
        iotlib::System::sleep(100);
        while (1)
        {
            tempSensor.startConversion();
            iotlib::System::sleep(1000);
            int16_t tmp = tempSensor.readRawTemperature();
            tmp >>= 4;

            ESP_LOGI("tmp", "tmp: %d", tmp);

            bool isParasite = iotlib::DS18B20::isAnyUsingParasitePower(oneWire);
            ESP_LOGI("1w", "is parasite: %d", (int)isParasite);
        }
        /*for (size_t i = 0; i < 9; i++)
        {
            uint8_t x = oneWire.readUint8();
            ESP_LOGI("1w", "data: %d", x);
        }*/

        /*ESP_LOGI("test timer", "0 %d", xx_time_get_time());
        iotlib::System::waitUs(1);
        ESP_LOGI("test timer", "1 %d", xx_time_get_time());
        iotlib::System::waitUs(5);
        ESP_LOGI("test timer", "5 %d", xx_time_get_time());
        iotlib::System::waitUs(10);
        ESP_LOGI("test timer", "10 %d", xx_time_get_time());
        iotlib::System::waitUs(15);
        ESP_LOGI("test timer", "15 %d", xx_time_get_time());
        iotlib::System::waitUs(20);
        ESP_LOGI("test timer", "20 %d", xx_time_get_time());*/

        //iotlib::UARTPort serial(app::Debug, 74880, iotlib::UARTPort::Parity::None, iotlib::UARTPort::StopBits::One);

        //serial.print("Hello UART from esp!\n");
        //serial.print("And second line!\n");

        //iotlib::I2CBus* bus = new iotlib::I2CBus(iotlib::esp8266::I2C_Bus0, iotlib::esp8266::I2C_SDA_GPIO4, iotlib::esp8266::I2C_SCL_GPIO5);
        iotlib::SPIBus* bus = new iotlib::SPIBus(iotlib::esp8266::SPI_BusHSPI);
        iotlib::BME280* bme280 = new iotlib::BME280(*bus, iotlib::esp8266::GPIO5);

        
        while (1)
        {
            iotlib::BME280::Result data;
            bme280->getData(data);

            ESP_LOGI("main", "bme temp hum press: %d %d %d", data.Temperature, data.Humidity, data.Pressure);
            iotlib::System::sleep(2000);
        }
    }
}

