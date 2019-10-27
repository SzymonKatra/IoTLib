#pragma once

#include <stdint.h>
#include "I2CBus.hpp"
#include "Internal/BoschSensortecBME280_driver/bme280.h"

namespace iotlib
{
    class BME280;
    namespace internal
    {
        class BME280PrivateAccessor
        {
        public:
            static int8_t I2CRead(BME280& bme280, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
            static int8_t I2CWrite(BME280& bme280, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
        };
    }

    class BME280
    {
    private:
        I2CBus& bus;
        uint8_t address;
        struct bme280_dev device;
        uint8_t iotlibId;

    public:
        BME280(I2CBus& bus, uint8_t sdo = 0);
        ~BME280();

        void getData(bme280_data& result);

        friend class internal::BME280PrivateAccessor;

    private:
        int8_t I2CRead(uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
        int8_t I2CWrite(uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
    };
}