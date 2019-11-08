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

    void OneWireBus::writeUint8(uint8_t value)
    {
        for (size_t i = 0; i < 8; i++)
        {
            this->write(value & 1);
            value >>= 1;
        }
    }

    uint8_t OneWireBus::readUint8()
    {
        uint8_t value = 0;
        for (size_t i = 0; i < 8; i++)
        {
            if (this->read())
            {
                value |= (1 << i);
            }
        }

        return value;
    }
}