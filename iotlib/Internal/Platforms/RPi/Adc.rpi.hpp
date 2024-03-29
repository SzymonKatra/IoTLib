#pragma once

#include <stdint.h>

namespace iotlib
{
    namespace rpi
    {
        typedef int AdcPinDefinition;
        const AdcPinDefinition ADC_NONE = -1;// RPi does not have any ADC
    }

    typedef rpi::AdcPinDefinition AdcPinDefinition;

    class Adc
    {
    public:
        Adc(AdcPinDefinition pin, uint16_t maxMiliVolts);
        ~Adc();

        uint16_t readRaw();
        uint16_t readMilivolts();
    };
}