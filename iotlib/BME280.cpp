#include "BME280.hpp"

namespace iotlib
{
    BME280::BME280(I2CBus& bus, uint8_t sdo)
        : bus(bus)
    {
        address = sdo == 0 ? 0x76 : 0x77;
    }

    BME280::~BME280()
    {
        
    }
}