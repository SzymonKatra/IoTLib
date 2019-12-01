#pragma once

#include <stdint.h>
#include "../UARTPort.hpp"

namespace iotlib
{
    class PMS3003
    {
    public:
        struct Data
        {
            uint16_t PM1Indoor;
            uint16_t PM2_5Indoor;
            uint16_t PM10Indoor;
            uint16_t PM1Outdoor;
            uint16_t PM2_5Outdoor;
            uint16_t PM10Outdoor;
        };

        enum class Mode
        {
            Passive = 0,
            Active = 1
        };

        enum class ErrorCode
        {
            Ok,
            InvalidChecksum,
            InvalidStartChar,
            InvalidFrameLength,
            UartError
        };

    private:
        UARTPort& port;

    public:
        PMS3003(UARTPort& port);
        ~PMS3003();

        ErrorCode read(Data& result);
    };
}