#pragma once

#include <stdint.h>
#include <stddef.h>

namespace iotlib
{
    namespace rpi
    {
        typedef int I2CBusDefinition;
        const I2CBusDefinition I2C_Bus0 = 0;

        typedef int I2CSdaPinDefinition;
        const I2CSdaPinDefinition I2C_SDA_GPIO2 = 0;

        typedef int I2CSclPinDefinition;
        const I2CSdaPinDefinition I2C_SCL_GPIO3 = 0;
    }

    typedef rpi::I2CBusDefinition I2CBusDefinition;
    typedef rpi::I2CSdaPinDefinition I2CSdaPinDefinition;
    typedef rpi::I2CSclPinDefinition I2CSclPinDefinition;

    // todo: error handling
    class I2CBus
    {
    private:
        I2CBusDefinition bus;
        int fd;
        uint8_t* buffer;
        size_t bufferLength;
        size_t dataLength;

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
