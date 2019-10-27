#include "BME280.hpp"
#include "System.hpp"

namespace iotlib
{
    static uint8_t nextIotlibId = 0;
    static BME280* instances[5];

    static void bme280_delay_ms(uint32_t period);
    static int8_t bme280_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
    static int8_t bme280_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

    namespace internal
    {
        int8_t BME280PrivateAccessor::I2CRead(BME280& bme280, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
        {
            return bme280.I2CRead(reg_addr, reg_data, len);
        }
        int8_t BME280PrivateAccessor::I2CWrite(BME280& bme280, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
        {
            return bme280.I2CWrite(reg_addr, reg_data, len);
        }
    }

    BME280::BME280(I2CBus& bus, uint8_t sdo)
        : bus(bus)
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
        this->device.read = bme280_i2c_read;
        this->device.write = bme280_i2c_write;
        this->device.delay_ms = bme280_delay_ms;

        bme280_init(&this->device); // todo: error handling
    }

    BME280::~BME280()
    {
        instances[this->iotlibId] = NULL;
    }

    void BME280::getData(bme280_data& result)
    {
        bme280_get_sensor_data(BME280_ALL, &result, &this->device);
    }

    int8_t BME280::I2CRead(uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
    {
        this->bus.write(this->address, &reg_addr, 1, true);
        this->bus.read(this->address, reg_data, len, I2CBus::ReadAckMode::AckButLastNack, true);
        // todo: error handling

        return 0;
    }

    int8_t BME280::I2CWrite(uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
    {
        this->bus.beginWrite(this->address, true);
        this->bus.write(&reg_addr, 1);
        this->bus.write(reg_data, len);
        this->bus.endWrite();
        // todo: error handling

        return 0;
    }

    void bme280_delay_ms(uint32_t period)
    {
        System::delay(period);
    }

    int8_t bme280_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
    {
        BME280* bme280 = instances[dev_id];
        return internal::BME280PrivateAccessor::I2CRead(*bme280, reg_addr, reg_data, len);
    }

    int8_t bme280_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
    {
        BME280* bme280 = instances[dev_id];
        return internal::BME280PrivateAccessor::I2CWrite(*bme280, reg_addr, reg_data, len);
    }
}