#include "Device.hpp"

namespace iotlib
{
    void Device::write(uint8_t data)
    {
        this->write(&data, 1);
    }

    uint8_t Device::read()
    {
        uint8_t data;
        this->read(&data, 1);
        return data;
    }

    GpioDevice::GpioDevice(Gpio& gpio)
        : gpio(gpio)
    {
    }

    size_t GpioDevice::write(const void* data, size_t length)
    {
        if (length >= 1)
        {
            this->gpio.write(*(bool*)data);
            return 1;
        }
        return 0;
    }

    size_t GpioDevice::read(void* data, size_t length)
    {
        if (length >= 1)
        {
            *(bool*)data = this->gpio.read();
            return 1;
        }
        
        return 0;
    }

    AdcDevice::AdcDevice(Adc& adc)
        : adc(adc)
    {
    }

    size_t AdcDevice::write(const void* data, size_t length)
    {
        return 0;
    }

    size_t AdcDevice::read(void* data, size_t length)
    {
        if (length >= 2)
        {
            *(uint16_t*)data = this->adc.readMilivolts();
            return 2;
        }

        return 0;
    }

    I2CDevice::I2CDevice(I2CBus& i2cBus, uint8_t address)
        : i2cBus(i2cBus), address(address)
    {
    }

    size_t I2CDevice::write(const void* data, size_t length)
    {
        this->i2cBus.beginWrite(this->address);
        this->i2cBus.write((const uint8_t*)data, length);
        this->i2cBus.endWrite();
        return length;
    }

    size_t I2CDevice::read(void* data, size_t length)
    {
        this->i2cBus.read(this->address, (uint8_t*)data, length);
        return length;
    }

    SPIDevice::SPIDevice(SPIBus& spiBus)
        : spiBus(spiBus)
    {
    }

    size_t SPIDevice::write(const void* data, size_t length)
    {
        this->spiBus.write((const uint8_t*)data, length);
        return length;
    }

    size_t SPIDevice::read(void* data, size_t length)
    {
        this->spiBus.read((uint8_t*)data, length);
        return length;
    }

    UARTDevice::UARTDevice(UARTPort & uartPort)
        : uartPort(uartPort)
    {
    }

    size_t UARTDevice::write(const void* data, size_t length)
    {
        return this->uartPort.write((const uint8_t*)data, length);
    }

    size_t UARTDevice::read(void* data, size_t length)
    {
        return this->uartPort.read((uint8_t*)data, length);
    }

    OneWireDevice::OneWireDevice(OneWireBus& oneWireBus)
        : OneWireDevice(oneWireBus, OneWireBus::NoDevice)
    {
    }

    OneWireDevice::OneWireDevice(OneWireBus& oneWireBus, OneWireBus::Address address)
        : oneWireBus(oneWireBus), address(address)
    {
    }

    size_t OneWireDevice::write(const void* data, size_t length)
    {
        this->selectDevice();

        if (length >= 8)
        {
            this->oneWireBus.writeData<uint64_t>(*(const uint64_t*)data);
            return 8;
        }
        else if (length >= 4)
        {
            this->oneWireBus.writeData<uint32_t>(*(const uint32_t*)data);
            return 4;
        }
        else if (length >= 2)
        {
            this->oneWireBus.writeData<uint16_t>(*(const uint16_t*)data);
            return 2;
        }
        else if (length >= 1)
        {
            this->oneWireBus.writeData<uint8_t>(*(const uint8_t*)data);
            return 1;
        }

        return 0;
    }

    size_t OneWireDevice::read(void* data, size_t length)
    {
        this->selectDevice();

        if (length >= 8)
        {
            *(uint64_t*)data = this->oneWireBus.readData<uint64_t>();
            return 8;
        }
        else if (length >= 4)
        {
            *(uint32_t*)data = this->oneWireBus.readData<uint32_t>();
            return 4;
        }
        else if (length >= 2)
        {
            *(uint16_t*)data = this->oneWireBus.readData<uint16_t>();
            return 2;
        }
        else if (length >= 1)
        {
            *(uint8_t*)data = this->oneWireBus.readData<uint8_t>();
            return 1;
        }
        
        return 0;
    }

    void OneWireDevice::selectDevice()
    {
        if (this->address != OneWireBus::NoDevice)
        {
            this->oneWireBus.matchRom(this->address);
        }
        else
        {
            this->oneWireBus.skipRom();
        }
    }
}