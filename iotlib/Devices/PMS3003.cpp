#include "PMS3003.hpp"

namespace iotlib
{
    const uint8_t StartChar1 = 0x42;
    const uint8_t StartChar2 = 0x4D;
    const size_t FrameLen = 20;

    PMS3003::PMS3003(UARTPort& port)
        : port(port)
    {
    }

    PMS3003::~PMS3003()
    {

    }

    PMS3003::ErrorCode PMS3003::read(Data* result)
    {
        uint8_t buffer[FrameLen + 4];
        uint8_t* bufferPtr = buffer;

        if (this->port.read(bufferPtr, 1) != 1) return ErrorCode::UartError;
        if (*bufferPtr != StartChar1) return ErrorCode::InvalidStartChar;
        bufferPtr++;

        if (this->port.read(bufferPtr, 1) != 1) return ErrorCode::UartError;
        if (*bufferPtr != StartChar2) return ErrorCode::InvalidStartChar;
        bufferPtr++;

        size_t remaining = FrameLen + 2;
        while (remaining > 0)
        {
            size_t read = this->port.read(bufferPtr, remaining);
            if (read <= 0) return ErrorCode::UartError;
            remaining -= read;
            bufferPtr += read;
        }

        uint16_t frameLength = (buffer[2] << 8) | buffer[3]; // Frame length
        if (frameLength != FrameLen) return ErrorCode::InvalidFrameLength;

        result->PM1Indoor = (buffer[4] << 8) | buffer[5]; // Data 1
        result->PM2_5Indoor = (buffer[6] << 8) | buffer[7]; // Data 2
        result->PM10Indoor = (buffer[8] << 8) | buffer[9]; // Data 3
        result->PM1Outdoor = (buffer[10] << 8) | buffer[11]; // Data 4
        result->PM2_5Outdoor = (buffer[12] << 8) | buffer[13]; // Data 5
        result->PM10Outdoor = (buffer[14] << 8) | buffer[15]; // Data 6

        uint16_t checksum = (buffer[22] << 8) | buffer[23]; // Data and check

        for (size_t i = 0; i < 22; i++)
        {
            checksum -= buffer[i];
        }

        if (checksum != 0) return ErrorCode::InvalidChecksum;

        return ErrorCode::Ok;
    }
}