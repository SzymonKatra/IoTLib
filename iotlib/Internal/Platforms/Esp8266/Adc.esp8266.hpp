#pragma once

#include <stdint.h>
#include <driver/adc.h>

namespace iotlib
{
    namespace esp8266
    {
        typedef adc_mode_t AdcPinDefinition;
        const AdcPinDefinition ADC_TOUT = ADC_READ_TOUT_MODE;
        const AdcPinDefinition ADC_VDD = ADC_READ_VDD_MODE;
    }

    typedef esp8266::AdcPinDefinition AdcPinDefinition;

    class Adc
    {
    private:
        AdcPinDefinition pin;
        uint16_t maxMiliVolts;

    public:
        Adc(AdcPinDefinition pin, uint16_t maxMiliVolts);
        ~Adc();

        uint16_t readRaw();
        uint16_t readMilivolts();
    };
}