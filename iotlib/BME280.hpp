#pragma once

#include <stdint.h>
#include "I2CBus.hpp"

namespace iotlib
{
    class BME280
    {
    private:
        I2CBus& bus;
        uint8_t address;

    public:
        BME280(I2CBus& bus, uint8_t sdo = 0);
        ~BME280();
    };
}