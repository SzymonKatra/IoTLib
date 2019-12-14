#include "BME280.hpp"
#include "../System.hpp"
#include <stdlib.h>
#include <string.h>

namespace iotlib
{
    static uint8_t nextIotlibId = 0;
    static BME280* instances[5];

    static void bme280_delay_ms(uint32_t period);
    static int8_t bme280_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
    static int8_t bme280_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

    namespace internal
    {
        int8_t BME280PrivateAccessor::deviceRead(BME280& bme280, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
        {
            return bme280.deviceRead(reg_addr, reg_data, len);
        }
        int8_t BME280PrivateAccessor::deviceWrite(BME280& bme280, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
        {
            return bme280.deviceWrite(reg_addr, reg_data, len);
        }
    }

    BME280::BME280(Device& device)
        : device(device)
    {
        this->iotlibId = nextIotlibId++;
        if (nextIotlibId >= 5)
        {
            System::error("Max number of BME280 sensors reached");
        }

        instances[this->iotlibId] = this;

        this->boschDriverDevice.dev_id = this->iotlibId;
        this->boschDriverDevice.intf = BME280_I2C_INTF; // todo: spi
        this->boschDriverDevice.read = bme280_read;
        this->boschDriverDevice.write = bme280_write;
        this->boschDriverDevice.delay_ms = bme280_delay_ms;

        bme280_init(&this->boschDriverDevice); // todo: error handling

        this->changeSettings(Oversampling::X1, Oversampling::X1, Oversampling::X1, FilterCoefficient::Disabled, StandbyTime::Ms20);
        this->setMode(Mode::Normal);
    }

    BME280::~BME280()
    {
        instances[this->iotlibId] = NULL;
    }

    void BME280::setMode(Mode mode)
    {
        bme280_set_sensor_mode((uint8_t)mode, &this->boschDriverDevice);
    }

    void BME280::changeSettings(Oversampling temperatureOversampling, Oversampling pressureOversampling, Oversampling humidityOversampling, FilterCoefficient filterCoefficient, StandbyTime standbyTime)
    {
        this->boschDriverDevice.settings.osr_t = (uint8_t)temperatureOversampling;
        this->boschDriverDevice.settings.osr_h = (uint8_t)humidityOversampling;
        this->boschDriverDevice.settings.osr_p = (uint8_t)pressureOversampling;
        this->boschDriverDevice.settings.filter = (uint8_t)filterCoefficient;
        this->boschDriverDevice.settings.standby_time = (uint8_t)standbyTime;
        bme280_set_sensor_settings(BME280_ALL_SETTINGS_SEL, &this->boschDriverDevice);
    }


    void BME280::getData(Result& result)
    {
        bme280_data data;
        bme280_get_sensor_data(BME280_ALL, &data, &this->boschDriverDevice);

        result.Temperature = data.temperature;
        result.Humidity = data.humidity;
        result.Pressure = data.pressure;
    }

    int8_t BME280::deviceRead(uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
    {
        this->device.write(reg_addr);
        this->device.read(reg_data, len);

        return 0;
    }

    int8_t BME280::deviceWrite(uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
    {
        uint8_t data[64];
        *data = reg_addr;
        memcpy(data + 1, reg_data, len);
        this->device.write(data, len + 1);

        return 0;
    }

    void bme280_delay_ms(uint32_t period)
    {
        System::sleep(period);
    }

    int8_t bme280_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
    {
        BME280* bme280 = instances[dev_id];
        return internal::BME280PrivateAccessor::deviceRead(*bme280, reg_addr, reg_data, len);
    }

    int8_t bme280_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
    {
        BME280* bme280 = instances[dev_id];
        return internal::BME280PrivateAccessor::deviceWrite(*bme280, reg_addr, reg_data, len);
    }
}