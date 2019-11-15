#include "OneWireBus.hpp"

#include "System.hpp"

namespace iotlib
{
    OneWireBus::OneWireBus(GpioPinDefinition busPin)
        : busPin(busPin)
    {
        Gpio::setup(this->busPin, Gpio::Direction::OutputOpenDrain);
        Gpio::write(this->busPin, true);
    }

    OneWireBus::~OneWireBus()
    {

    }

    bool OneWireBus::reset()
    {
        System::enterCritical();

        Gpio::write(this->busPin, false);
        System::waitUs(480);
        Gpio::write(this->busPin, true);
        System::waitUs(70);
        bool isDevicePresent = !Gpio::read(this->busPin);
        System::waitUs(410);

        System::leaveCritical();

        return isDevicePresent;
    }

    void OneWireBus::write(bool value)
    {
        System::enterCritical();

        Gpio::write(this->busPin, false);
        System::waitUs(value ? 6 : 60);
        Gpio::write(this->busPin, true);
        System::waitUs(value ? 64 : 10);

        System::leaveCritical();
    }

    bool OneWireBus::read()
    {
        System::enterCritical();

        Gpio::write(this->busPin, false);
        System::waitUs(6);
        Gpio::write(this->busPin, true);
        System::waitUs(9);
        bool sample = Gpio::read(this->busPin);
        System::waitUs(55);

        System::leaveCritical();

        return sample;
    }

    size_t OneWireBus::searchRom(uint64_t* array, size_t size)
    {
        if (!this->reset()) return 0;

        this->writeData(0xF0);
        
        // TODO
        return 0;
    }

    uint64_t OneWireBus::readRom()
    {
        if (!this->reset()) return 0;

        this->writeData<uint8_t>(0x33);
        return this->readData<uint64_t>();
    }

    void OneWireBus::matchRom(uint64_t address)
    {
        if (!this->reset()) return;

        this->writeData<uint8_t>(0x55);
        this->writeData<uint64_t>(address);
    }

    void OneWireBus::skipRom()
    {
        if (!this->reset()) return;

        this->writeData<uint8_t>(0xCC);
    }

    size_t OneWireBus::alarmSearch(uint64_t* array, size_t size)
    {
        if (!this->reset()) return 0;

        this->writeData<uint8_t>(0xEC);
        
        // TODO
        return 0;
    }
}