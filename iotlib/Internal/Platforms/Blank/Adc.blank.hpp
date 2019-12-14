#pragma once

#include <stdint.h>

namespace iotlib
{
    namespace blank
    {
        typedef int AdcPinDefinition;
    }

    typedef blank::AdcPinDefinition AdcPinDefinition;

    class Adc
    {
    public:
        Adc(AdcPinDefinition pin, uint16_t maxMiliVolts);
        ~Adc();

        uint16_t readRaw();
        uint16_t readMilivolts();
    };
}