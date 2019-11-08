#pragma once

#include "Gpio.hpp"
#include <stdint.h>

namespace iotlib
{
    class OneWireBus
    {
    private:
        GpioPinDefinition busPin;

    public:
        OneWireBus(GpioPinDefinition busPin);
        ~OneWireBus();

        bool reset();
        void write(bool value);
        bool read();

        void writeUint8(uint8_t value);
        uint8_t readUint8();
    };
}