#pragma once

#include <stdint.h>
namespace iotlib
{
    namespace blank
    {
        typedef int I2CBusDefinition;

        typedef int I2CSdaPinDefinition;

        typedef int I2CSclPinDefinition;
    }

    typedef blank::I2CBusDefinition I2CBusDefinition;
    typedef blank::I2CSdaPinDefinition I2CSdaPinDefinition;
    typedef blank::I2CSclPinDefinition I2CSclPinDefinition;

    class I2CBus
    {
    public:
        I2CBus(I2CBusDefinition bus, I2CSdaPinDefinition sdaPin, I2CSclPinDefinition sclPin);
        ~I2CBus();

        void write(uint8_t address, const uint8_t* data, size_t length);
        void read(uint8_t address, uint8_t* data, size_t length);

        void beginWrite(uint8_t address);
        void write(const uint8_t* data, size_t length);
        void endWrite();

        bool isDevicePresent(uint8_t address);
    };
}