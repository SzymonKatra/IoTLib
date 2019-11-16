#include "BME280.hpp"
#include "../System.hpp"
#include <stdlib.h>
#include <string.h>
#include <esp_log.h>

namespace iotlib
{
    static uint8_t nextIotlibId = 0;
    static BME280* instances[5];

    static void bme280_delay_ms(uint32_t period);
    static int8_t bme280_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
    static int8_t bme280_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

    namespace internal
    {
        int8_t BME280PrivateAccessor::busRead(BME280& bme280, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
        {
            return bme280.busRead(reg_addr, reg_data, len);
        }
        int8_t BME280PrivateAccessor::busWrite(BME280& bme280, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
        {
            return bme280.busWrite(reg_addr, reg_data, len);
        }
    }

    BME280::BME280(I2CBus& bus, uint8_t sdo)
        : i2cBus(&bus), spiBus(NULL), csGpio(Gpio::createDummy())
    {
        this->iotlibId = nextIotlibId++;
        if (nextIotlibId >= 5)
        {
            System::error("Max number of BME280 sensors reached");
        }

        instances[this->iotlibId] = this;

        address = sdo == 0 ? BME280_I2C_ADDR_PRIM : BME280_I2C_ADDR_SEC;

        this->device.dev_id = this->iotlibId;
        this->device.intf = BME280_I2C_INTF;
        this->device.read = bme280_read;
        this->device.write = bme280_write;
        this->device.delay_ms = bme280_delay_ms;

        bme280_init(&this->device); // todo: error handling

        this->changeSettings(Oversampling::X1, Oversampling::X1, Oversampling::X1, FilterCoefficient::Disabled, StandbyTime::Ms20);
        this->setMode(Mode::Normal);
    }

    BME280::BME280(SPIBus& bus, GpioPinDefinition csPin)
        : i2cBus(NULL), spiBus(&bus), csGpio(csPin, Gpio::Direction::Output)
    {
        csGpio.write(true);

        this->iotlibId = nextIotlibId++;
        if (nextIotlibId >= 5)
        {
            System::error("Max number of BME280 sensors reached");
        }

        instances[this->iotlibId] = this;

        //address = sdo == 0 ? BME280_I2C_ADDR_PRIM : BME280_I2C_ADDR_SEC;

        this->device.dev_id = this->iotlibId;
        this->device.intf = BME280_SPI_INTF;
        this->device.read = bme280_read;
        this->device.write = bme280_write;
        this->device.delay_ms = bme280_delay_ms;

        bme280_init(&this->device); // todo: error handling

        this->changeSettings(Oversampling::X1, Oversampling::X1, Oversampling::X1, FilterCoefficient::Disabled, StandbyTime::Ms20);
        this->setMode(Mode::Normal);
    }

    BME280::~BME280()
    {
        instances[this->iotlibId] = NULL;
    }

    void BME280::setMode(Mode mode)
    {
        bme280_set_sensor_mode((uint8_t)mode, &this->device);
    }

    void BME280::changeSettings(Oversampling temperatureOversampling, Oversampling pressureOversampling, Oversampling humidityOversampling, FilterCoefficient filterCoefficient, StandbyTime standbyTime)
    {
        this->device.settings.osr_t = (uint8_t)temperatureOversampling;
        this->device.settings.osr_h = (uint8_t)humidityOversampling;
        this->device.settings.osr_p = (uint8_t)pressureOversampling;
        this->device.settings.filter = (uint8_t)filterCoefficient;
        this->device.settings.standby_time = (uint8_t)standbyTime;
        bme280_set_sensor_settings(BME280_ALL_SETTINGS_SEL, &this->device);
    }


    void BME280::getData(Result& result)
    {
        bme280_data data;
        bme280_get_sensor_data(BME280_ALL, &data, &this->device);

        result.Temperature = data.temperature;
        result.Humidity = result.Humidity;
        result.Pressure = result.Pressure;
    }

    int8_t BME280::busRead(uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
    {
        if (this->device.intf == BME280_I2C_INTF)
        {
            this->i2cBus->write(this->address, &reg_addr, 1);
            this->i2cBus->read(this->address, reg_data, len);
        }
        else
        {
            //ESP_LOGI("BME280", "READ, reg_addr = %02X, len = %d", reg_addr, len);
            System::sleep(10); // why without this bme280 returns wrong results.. wtf?
            csGpio.write(false);
            this->spiBus->write(&reg_addr, 1);
            this->spiBus->read(reg_data, len);
            csGpio.write(true);

            /*for (size_t i = 0; i < len; i++)
            {
                ESP_LOGI("BME280", "%d: %02X", i, reg_data[i]);
            }*/
        }
        // todo: error handling

        return 0;
    }

    int8_t BME280::busWrite(uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
    {
        if (this->device.intf == BME280_I2C_INTF)
        {
            this->i2cBus->beginWrite(this->address);
            this->i2cBus->write(&reg_addr, 1);
            this->i2cBus->write(reg_data, len);
            this->i2cBus->endWrite();
        }
        else
        {
            /*ESP_LOGI("BME280", "WRITE, reg_addr = %02X, len = %d", reg_addr, len);
            for (size_t i = 0; i < len; i++)
            {
                ESP_LOGI("BME280", "%d: %02X", i, reg_data[i]);
            }*/

            csGpio.write(false);
            this->spiBus->write(&reg_addr, 1);
            this->spiBus->write(reg_data, len);
            csGpio.write(true);
        }
        // todo: error handling

        return 0;
    }

    void bme280_delay_ms(uint32_t period)
    {
        System::sleep(period);
    }

    int8_t bme280_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
    {
        BME280* bme280 = instances[dev_id];
        return internal::BME280PrivateAccessor::busRead(*bme280, reg_addr, reg_data, len);
    }

    int8_t bme280_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
    {
        BME280* bme280 = instances[dev_id];
        return internal::BME280PrivateAccessor::busWrite(*bme280, reg_addr, reg_data, len);
    }

    int8_t bme280_spi_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
    {
        //BME280* bme280 = instances[dev_id];

        int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

        /*
         * The parameter dev_id can be used as a variable to select which Chip Select pin has
         * to be set low to activate the relevant device on the SPI bus
         */

         /*
          * Data on the bus should be like
          * |----------------+---------------------+-------------|
          * | MOSI           | MISO                | Chip Select |
          * |----------------+---------------------|-------------|
          * | (don't care)   | (don't care)        | HIGH        |
          * | (reg_addr)     | (don't care)        | LOW         |
          * | (don't care)   | (reg_data[0])       | LOW         |
          * | (....)         | (....)              | LOW         |
          * | (don't care)   | (reg_data[len - 1]) | LOW         |
          * | (don't care)   | (don't care)        | HIGH        |
          * |----------------+---------------------|-------------|
          */

        return rslt;
    }

    int8_t bme280_spi_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
    {
        //BME280* bme280 = instances[dev_id];

        int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

        /*
         * The parameter dev_id can be used as a variable to select which Chip Select pin has
         * to be set low to activate the relevant device on the SPI bus
         */

         /*
          * Data on the bus should be like
          * |---------------------+--------------+-------------|
          * | MOSI                | MISO         | Chip Select |
          * |---------------------+--------------|-------------|
          * | (don't care)        | (don't care) | HIGH        |
          * | (reg_addr)          | (don't care) | LOW         |
          * | (reg_data[0])       | (don't care) | LOW         |
          * | (....)              | (....)       | LOW         |
          * | (reg_data[len - 1]) | (don't care) | LOW         |
          * | (don't care)        | (don't care) | HIGH        |
          * |---------------------+--------------|-------------|
          */

        return rslt;
    }
}