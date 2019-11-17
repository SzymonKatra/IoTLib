#include <string.h>
#include <string>
#include "I2CBus.rpi.hpp"
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../../System.hpp"
#include "bcm2835.h"

namespace iotlib
{
    I2CBus::I2CBus(I2CBusDefinition bus, I2CSdaPinDefinition sdaPin, I2CSclPinDefinition sclPin)
        : bus(bus)
    {
        bcm2835_i2c_begin();
    }
    I2CBus::~I2CBus()
    {
        bcm2835_i2c_end();
    }

    void I2CBus::write(uint8_t address, const uint8_t* data, size_t length)
    {
        bcm2835_i2c_setSlaveAddress(address);
        bcm2835_i2c_write((const char*)data, length);
    }

    void I2CBus::read(uint8_t address, uint8_t* data, size_t length)
    {
        bcm2835_i2c_setSlaveAddress(address);
        bcm2835_i2c_read((char*)data, length);
    }

    void I2CBus::beginWrite(uint8_t address)
    {
        bcm2835_i2c_setSlaveAddress(address);

        this->bufferLength = 256;
        this->dataLength = 0;
        this->buffer = (uint8_t*)malloc(this->bufferLength);
    }

    void I2CBus::write(const uint8_t* data, size_t length)
    {
        size_t remainingBuffer = this->bufferLength - this->dataLength;
        if (length > remainingBuffer)
        {
            size_t required = this->dataLength + length;
            this->bufferLength *= 2;
            if (this->bufferLength < required) this->bufferLength = required;
            this->buffer = (uint8_t*)realloc(this->buffer, this->bufferLength);
        }
        memcpy(this->buffer + this->dataLength, data, length);
        this->dataLength += length;
    }

    void I2CBus::endWrite()
    {
        bcm2835_i2c_write((const char*)this->buffer, this->dataLength);
        free(this->buffer);
    }
}
