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
#include <iotlib/Devices/MCP9700.hpp>
#include <iotlib/Devices/PMS3003.hpp>
#include <iotlib/Devices/HD44780.hpp>
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

        //iotlib::SPIBus spi(iotlib::esp8266::SPI_BusHSPI);
        //uint8_t x[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0x11, 0x22, 0x33, 0x44 };
        //spi.write(x, 8);
        //iotlib::System::sleep(5000);

        //iotlib::OneWireBus::Address addresses[10];

        //iotlib::OneWireBus oneWire(iotlib::esp8266::GPIO4);
        //
        //iotlib::Adc adc(iotlib::esp8266::ADC_TOUT, 3300);
        //iotlib::MCP9700 analogTemp(adc);
        //iotlib::System::sleep(100);
        //iotlib::PMS3003::Data pmsData;
        ////oneWire.readRom();
        //size_t devCount = oneWire.search(iotlib::OneWireBus::SearchType::SearchRom, addresses, 10);
        //ESP_LOGI("1w", "dev cnt %d", devCount);
        //for (size_t i = 0; i < devCount; i++)
        //{
        //    iotlib::OneWireBus::Address addrx = addresses[i];
        //    uint64_t addr = addrx.Value;
        //    ESP_LOGI("1w", "addr H:%08X L:%08X, family: %02X, serial %04X%08X, crc: %02X", (uint32_t)(addr >> 32), (uint32_t)(addr), addrx.FamilyCode, (uint32_t)(addrx.SerialNumber >> 32), (uint32_t)addrx.SerialNumber, addrx.Crc);
        //}
        ///*{
        //    iotlib::UARTPort uart(iotlib::esp8266::UART_Port0Swapped, 9600, iotlib::UARTPort::Parity::None, iotlib::UARTPort::StopBits::One);
        //    iotlib::PMS3003 pms3003(uart);
        //    while (pms3003.read(&pmsData) != iotlib::PMS3003::ErrorCode::Ok);
        //}*/
        //    iotlib::System::sleep(2000);
        //
        //    iotlib::DS18B20 tempSensor(oneWire, addresses[0]);
        //    iotlib::DS18B20 tempSensor2(oneWire, addresses[1]);
        //ESP_LOGI("pms3003", "pm1 %d, pm25 %d, pm10 %d", pmsData.PM1Outdoor, pmsData.PM2_5Outdoor, pmsData.PM10Outdoor);
        //while (1)
        //{
        //    iotlib::DS18B20::allStartConversion(oneWire);
        //    //tempSensor.startConversion();
        //    iotlib::System::sleep(1000);
        //    int16_t tmp = tempSensor.readRawTemperature();
        //    tmp >>= 4;
        //    int16_t tmp2 = tempSensor2.readRawTemperature();
        //    tmp2 >>= 4;

        //    ESP_LOGI("tmp", "tmp: %d, tmp2: %d", tmp, tmp2);

        //    bool isParasite = iotlib::DS18B20::isAnyUsingParasitePower(oneWire);
        //    ESP_LOGI("1w", "is parasite: %d", (int)isParasite);

        //    uint16_t adcr = adc.readMilivolts();
        //    ESP_LOGI("adc", "%d", adcr);

        //    int8_t temp = analogTemp.readTemperature();
        //    ESP_LOGI("mcp9700", "%d", temp);
        //}
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

        iotlib::I2CBus* bus = new iotlib::I2CBus(iotlib::esp8266::I2C_Bus0, iotlib::esp8266::I2C_SDA_GPIO4, iotlib::esp8266::I2C_SCL_GPIO5);
        iotlib::HD44780 lcd(*bus, 0x27);
        uint8_t customch[8] = { 0xFF, 0x0E, 0x15, 0x10, 0x10, 0x11, 0x0E, 0x00 };
        lcd.text("test lcd");
        
        iotlib::System::sleep(2000);
        lcd.data('x');
        lcd.defineChar(1, customch);
        lcd.cursorGoTo(0, 1);
        lcd.data(1);
        lcd.data('y');

        bool blink = true;
        while (true)
        {
            iotlib::System::sleep(2000);
            lcd.displayControl(true, false, blink);
            blink = !blink;
        }
        /*iotlib::SPIBus* bus = new iotlib::SPIBus(iotlib::esp8266::SPI_BusHSPI);
        iotlib::BME280* bme280 = new iotlib::BME280(*bus, iotlib::esp8266::GPIO5);
        iotlib::OneWireBus oneWire(iotlib::esp8266::GPIO4);
        oneWire.searchBegin(iotlib::OneWireBus::SearchType::SearchRom);
        iotlib::OneWireBus::Address dsAddr = oneWire.searchNext();
        iotlib::DS18B20 tempDS(oneWire, dsAddr);

        while (1)
        {
            iotlib::BME280::Result data;
            bme280->getData(data);

            ESP_LOGI("main", "bme temp hum press: %d %d %d", data.Temperature, data.Humidity, data.Pressure);
            ESP_LOGI("main", "ds18b20 temp: %d", (tempDS.readRawTemperature() >> 4));
            iotlib::System::sleep(2000);
            tempDS.startConversion();
        }*/
    }
}

