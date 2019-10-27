#include <string.h>
#include <string>
#include "I2CBus.rpi.hpp"
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../System.hpp"

namespace iotlib
{
    I2CBus::I2CBus(I2CBusDefinition bus, I2CSdaPinDefinition sdaPin, I2CSclPinDefinition sclPin)
        : bus(bus)
    {
        this->fd = open(("/dev/i2c-" + std::to_string(bus)).c_str(), O_RDWR);
        if (this->fd < 0)
        {
            System::error("Cannot open I2C bus");
        }
    }
    I2CBus::~I2CBus()
    {
        close(this->fd);
    }

    void I2CBus::write(uint8_t address, const uint8_t* data, size_t length)
    {
        this->selectDevice(address);

        ::write(this->fd, data, length);
    }

    void I2CBus::read(uint8_t address, uint8_t* data, size_t length)
    {
        this->selectDevice(address);

        ::read(this->fd, data, length);
    }

    void I2CBus::beginWrite(uint8_t address)
    {
        this->selectDevice(address);

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
        ::write(this->fd, this->buffer, this->dataLength);
        free(this->buffer);
    }

    void I2CBus::selectDevice(uint8_t address)
    {
        if (ioctl(this->fd, I2C_SLAVE, address) < 0)
        {
            System::error("Cannot select I2C device");
        }
    }
}
