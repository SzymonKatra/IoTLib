#include "OneWireBus.hpp"

#include "System.hpp"
#include <esp_log.h>

namespace iotlib
{
    OneWireBus::Address::Address()
    {
    }
    OneWireBus::Address::Address(uint64_t value)
        : Value(value)
    {
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

    OneWireBus::OneWireBus(GpioPinDefinition busPin)
        : busGpio(busPin, Gpio::Direction::OutputOpenDrain, true)
    {
    }

    OneWireBus::~OneWireBus()
    {

    }

    bool OneWireBus::reset()
    {
        System::enterCritical();

        busGpio.write(false);
        System::waitUs(480);
        busGpio.write(true);
        System::waitUs(70);
        bool isDevicePresent = !busGpio.read();
        System::waitUs(410);

        System::leaveCritical();

        return isDevicePresent;
    }

    void OneWireBus::write(bool value)
    {
        System::enterCritical();

        busGpio.write(false);
        System::waitUs(value ? 6 : 60);
        busGpio.write(true);
        System::waitUs(value ? 64 : 10);

        System::leaveCritical();
    }

    bool OneWireBus::read()
    {
        System::enterCritical();

        busGpio.write(false);
        System::waitUs(6);
        busGpio.write(true);
        System::waitUs(9);
        bool sample = busGpio.read();
        System::waitUs(55);

        System::leaveCritical();

        return sample;
    }

    void OneWireBus::searchBegin(OneWireBus::SearchType searchType)
    {
        this->currentSearchType = searchType;
        this->lastDeviceAddress = 0;
        this->lastDiscrepancy = -1;
    }

    OneWireBus::Address OneWireBus::searchNext()
    {
        if (this->lastDeviceAddress != 0 && this->lastDiscrepancy == -1) return OneWireBus::NoDevice;

        if (!this->reset()) return OneWireBus::NoDevice;

        this->writeData<uint8_t>((uint8_t)this->currentSearchType);

        uint64_t deviceAddress = 0;
        int8_t bitNumber = 0;
        int8_t lastZero = -1;

        while (bitNumber < 64)
        {
            bool actual = this->read();
            bool complement = this->read();

            bool path;

            if (actual != complement)
            {
                path = actual;
            }
            else
            {
                if (actual && complement) return OneWireBus::NoDevice;

                if (bitNumber < this->lastDiscrepancy)
                {
                    path = this->lastDeviceAddress & ((uint64_t)1 << bitNumber);
                }
                else
                {
                    path = bitNumber == this->lastDiscrepancy;
                }

                if (!path)
                {
                    lastZero = bitNumber;
                }
            }

            this->write(path);
            if (path)
            {
                deviceAddress |= ((uint64_t)1 << bitNumber);
            }

            bitNumber++;
        }

        this->lastDeviceAddress = deviceAddress;
        this->lastDiscrepancy = lastZero;

        return Address(deviceAddress);
    }

    size_t OneWireBus::search(SearchType searchType, Address* array, size_t size)
    {
        size_t devicesCount = 0;
        Address deviceAddress;

        this->searchBegin(searchType);
        deviceAddress = this->searchNext();
        while (deviceAddress != OneWireBus::NoDevice && devicesCount < size)
        {
            *array = deviceAddress;
            array++;
            devicesCount++;

            deviceAddress = this->searchNext();
        }

        return devicesCount;
    }

    uint64_t OneWireBus::readRom()
    {
        if (!this->reset()) return 0;

        this->writeData<uint8_t>(0x33);
        return this->readData<uint64_t>();
    }

    void OneWireBus::matchRom(Address address)
    {
        if (!this->reset()) return;

        this->writeData<uint8_t>(0x55);
        this->writeData<uint64_t>(address.Value);
    }

    void OneWireBus::skipRom()
    {
        if (!this->reset()) return;

        this->writeData<uint8_t>(0xCC);
    }
}