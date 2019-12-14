#include "I2CBus.blank.hpp"

namespace iotlib
{
    I2CBus::I2CBus(I2CBusDefinition bus, I2CSdaPinDefinition sdaPin, I2CSclPinDefinition sclPin)
    {
        #warning Not implemented!
    }
    I2CBus::~I2CBus()
    {
        #warning Not implemented!
    }

    void I2CBus::write(uint8_t address, const uint8_t* data, size_t length)
    {
        #warning Not implemented!
    }

    void I2CBus::read(uint8_t address, uint8_t* data, size_t length)
    {
        #warning Not implemented!
    }

    void I2CBus::beginWrite(uint8_t address)
    {
        #warning Not implemented!
    }

    void I2CBus::write(const uint8_t* data, size_t length)
    {
        #warning Not implemented!
    }

    void I2CBus::endWrite()
    {
        #warning Not implemented!
    }

    bool I2CBus::isDevicePresent(uint8_t address)
    {
        #warning Not implemented!
    }
}