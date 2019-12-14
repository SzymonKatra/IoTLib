#include "Adc.esp8266.hpp"

namespace iotlib
{
    Adc::Adc(AdcPinDefinition pin, uint16_t maxMiliVolts)
        : pin(pin), maxMiliVolts(maxMiliVolts)
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

    uint16_t Adc::readRaw()
    {
        uint16_t result;
        adc_read(&result);
        return result;
    }

    uint16_t Adc::readMilivolts()
    {
        uint32_t normalized = (this->readRaw() * 1000) / 1023;

        return (normalized * this->maxMiliVolts) / 1000;
    }
}