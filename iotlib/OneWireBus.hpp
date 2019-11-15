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

        template<typename T>
        void writeData(T value)
        {
            for (size_t i = 0; i < sizeof(T) * 8; i++)
            {
                this->write(value & 1);
                value >>= 1;
            }
        }

        template<typename T>
        T readData()
        {
            T value = 0;
            for (size_t i = 0; i < sizeof(T) * 8; i++)
            {
                if (this->read())
                {
                    value |= (1 << i);
                }
            }

            return value;
        }

        size_t searchRom(uint64_t* array, size_t size);
        uint64_t readRom();
        void matchRom(uint64_t address);
        void skipRom();
        size_t alarmSearch(uint64_t* array, size_t size);
    };
}