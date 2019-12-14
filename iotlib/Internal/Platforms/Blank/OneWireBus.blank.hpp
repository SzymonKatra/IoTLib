#pragma once

#include <stdint.h>
#include <stddef.h>

namespace iotlib
{
    namespace blank
    {
        typedef int OneWireBusDefinition;
    }

    typedef blank::OneWireBusDefinition OneWireBusDefinition;

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

    public:
        OneWireBus(OneWireBusDefinition oneWireGpioPin);
        ~OneWireBus();

        bool reset();
        void write(bool value);
        bool read();

        template<typename T>
        void writeData(T value)
        {
            #warning Not implemented!
        }

        template<typename T>
        T readData()
        {
            #warning Not implemented!
        }

        void searchBegin(SearchType searchType);
        Address searchNext();
        size_t search(SearchType searchType, Address* result, size_t size);

        Address readRom();
        void matchRom(Address address);
        void skipRom();
    };
}