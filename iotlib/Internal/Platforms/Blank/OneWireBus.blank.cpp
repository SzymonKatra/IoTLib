#include "OneWireBus.blank.hpp"

namespace iotlib
{
    OneWireBus::Address::Address()
    {
        #warning Not implemented!
    }
    OneWireBus::Address::Address(uint64_t value)
    {
        #warning Not implemented!
    }

    bool OneWireBus::Address::operator==(const Address& other)
    {
        return this->Value == other.Value;
    }

    bool OneWireBus::Address::operator!=(const Address& other)
    {
        return this->Value != other.Value;
    }

    OneWireBus::Address OneWireBus::NoDevice = OneWireBus::Address(0);

    OneWireBus::OneWireBus(OneWireBusDefinition oneWireGpioPin)
    {
        #warning Not implemented!
    }

    OneWireBus::~OneWireBus()
    {
        #warning Not implemented!
    }

    bool OneWireBus::reset()
    {
        #warning Not implemented!
    }

    void OneWireBus::write(bool value)
    {
        #warning Not implemented!
    }

    bool OneWireBus::read()
    {
        #warning Not implemented!
    }

    void OneWireBus::searchBegin(OneWireBus::SearchType searchType)
    {
        #warning Not implemented!
    }

    OneWireBus::Address OneWireBus::searchNext()
    {
        #warning Not implemented!
    }

    size_t OneWireBus::search(SearchType searchType, Address* array, size_t size)
    {
        #warning Not implemented!
    }

    OneWireBus::Address OneWireBus::readRom()
    {
        #warning Not implemented!
    }

    void OneWireBus::matchRom(Address address)
    {
        #warning Not implemented!
    }

    void OneWireBus::skipRom()
    {
        #warning Not implemented!
    }
}