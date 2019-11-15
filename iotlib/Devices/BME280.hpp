#pragma once

#include <stdint.h>
#include "../I2CBus.hpp"
#include "../SPIBus.hpp"
#include "../Gpio.hpp"
#include "../Internal/BoschSensortecBME280_driver/bme280.h"

namespace iotlib
{
    class BME280;
    namespace internal
    {
        class BME280PrivateAccessor
        {
        public:
            static int8_t busRead(BME280& bme280, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
            static int8_t busWrite(BME280& bme280, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
        };
    }

    class BME280
    {
    public:
        struct Result
        {
            uint32_t Pressure;
            int32_t Temperature;
            uint32_t Humidity;
        };
        enum class Mode
        {
            Sleep = BME280_SLEEP_MODE,
            Forced = BME280_FORCED_MODE,
            Normal = BME280_NORMAL_MODE
        };
        enum class Oversampling
        {
            None = BME280_NO_OVERSAMPLING,
            X1 = BME280_OVERSAMPLING_1X,
            X2 = BME280_OVERSAMPLING_2X,
            X4 = BME280_OVERSAMPLING_4X,
            X8 = BME280_OVERSAMPLING_8X,
            X16 = BME280_OVERSAMPLING_16X
        };
        enum class FilterCoefficient
        {
            Disabled = BME280_FILTER_COEFF_OFF,
            F2 = BME280_FILTER_COEFF_2,
            F4 = BME280_FILTER_COEFF_4,
            F8 = BME280_FILTER_COEFF_8,
            F16 = BME280_FILTER_COEFF_16
        };
        enum class StandbyTime
        {
            Ms0_5 = BME280_STANDBY_TIME_0_5_MS,
            Ms62_5 = BME280_STANDBY_TIME_62_5_MS,
            Ms125 = BME280_STANDBY_TIME_125_MS,
            Ms250 = BME280_STANDBY_TIME_250_MS,
            Ms500 = BME280_STANDBY_TIME_500_MS,
            Ms1000 = BME280_STANDBY_TIME_1000_MS,
            Ms10 = BME280_STANDBY_TIME_10_MS,
            Ms20 = BME280_STANDBY_TIME_20_MS
        };

    private:
        I2CBus* i2cBus;
        SPIBus* spiBus;
        uint8_t address;
        struct bme280_dev device;
        uint8_t iotlibId;
        GpioPinDefinition csPin;

    public:
        BME280(I2CBus& bus, uint8_t sdo = 0);
        BME280(SPIBus& bus, GpioPinDefinition csPin);
        ~BME280();

        void setMode(Mode mode);
        void changeSettings(Oversampling temperatureOversampling, Oversampling pressureOversampling, Oversampling humidityOversampling, FilterCoefficient filterCoefficient, StandbyTime standbyTime);

        void getData(Result& result);

        friend class internal::BME280PrivateAccessor;

    private:
        int8_t busRead(uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
        int8_t busWrite(uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
    };
}