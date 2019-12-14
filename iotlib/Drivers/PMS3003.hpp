#pragma once

#include <stdint.h>
#include "../Device.hpp"

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
            DeviceError
        };

    private:
        Device& device;

    public:
        PMS3003(Device& device);
        ~PMS3003();

        ErrorCode read(Data& result);
    };
}