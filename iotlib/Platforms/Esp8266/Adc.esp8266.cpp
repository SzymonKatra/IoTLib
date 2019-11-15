#include "Adc.esp8266.hpp"

namespace iotlib
{
    Adc::Adc(AdcPinDefinition pin)
    {
        adc_config_t config;
        config.mode = pin;
        config.clk_div = 8;
        adc_init(&config);
    }

    Adc::~Adc()
    {
        adc_deinit();
    }

    uint16_t Adc::read()
    {
        uint16_t result;
        adc_read(&result);
        return result;
    }
}