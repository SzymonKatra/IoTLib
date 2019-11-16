#pragma once

#include "Gpio.hpp"
#include <stdint.h>

namespace iotlib
{
    class OneWireBus
    {
    public:
        union Address
        {
            uint64_t Value;
            struct
            {
                uint8_t FamilyCode : 8;
                uint64_t SerialNumber : 48;
                uint8_t Crc : 8;
            };

            Address();
            Address(uint64_t value);

            bool operator==(const Address& other);
            bool operator!=(const Address& other);
        };

        static Address NoDevice;

        enum class SearchType
        {
            SearchRom = 0xF0,
            AlarmSearch = 0xEC
        };

    private:
        Gpio busGpio;
        SearchType currentSearchType;
        uint64_t lastDeviceAddress;
        int8_t lastDiscrepancy;

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

        void searchBegin(SearchType searchType);
        Address searchNext();
        size_t search(SearchType searchType, Address* result, size_t size);

        Address readRom();
        void matchRom(Address address);
        void skipRom();
    };
}