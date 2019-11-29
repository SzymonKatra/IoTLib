#pragma once

#include "../OneWireBus.hpp"
#include <stdint.h>

namespace iotlib
{
    class DS18B20
    {
    public:
        enum class Resolution
        {
            R9Bits = 0b00011111,
            R10Bits = 0b00111111,
            R11Bits = 0b01011111,
            R12Bits = 0b01111111
        };

    private:
        OneWireBus& bus;
        OneWireBus::Address address;

    public:
        DS18B20(OneWireBus& bus);
        DS18B20(OneWireBus& bus, OneWireBus::Address address);
        ~DS18B20();

        void startConversion();
        void setResolution(Resolution resolution);
        int16_t readRawTemperature();

        const OneWireBus::Address& getAddress();

        static bool isAnyUsingParasitePower(OneWireBus& bus);
        static void allStartConversion(OneWireBus& bus);

    private:
        void selectDevice();

        void writeScratchpad(uint8_t th, uint8_t tl, uint8_t configReg);
    };
}