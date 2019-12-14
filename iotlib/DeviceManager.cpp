#include "DeviceManager.hpp"

namespace iotlib
{
    DeviceManager::DeviceManager()
        : currentIndex(0), dummyGpio(Gpio::createDummy())
    {
    }
    DeviceManager::~DeviceManager()
    {
        for (size_t i = 0; i < this->currentIndex; i++)
        {
            delete this->registeredDevices[i];
        }
    }

    Device& DeviceManager::createAdcDevice(Adc & adc)
    {
        AdcDevice* device = new AdcDevice(adc);
        this->registeredDevices[this->currentIndex++] = device;
        return *device;
    }

    Device& DeviceManager::createGpioDevice(Gpio & gpio)
    {
        GpioDevice* device = new GpioDevice(gpio);
        this->registeredDevices[this->currentIndex++] = device;
        return *device;
    }

    Device& DeviceManager::createI2CDevice(I2CBus & i2cBus, uint8_t address)
    {
        I2CDevice* device = new I2CDevice(i2cBus, address);
        this->registeredDevices[this->currentIndex++] = device;
        return *device;
    }

    Device& DeviceManager::createOneWireDevice(OneWireBus & oneWireBus)
    {
        return this->createOneWireDevice(oneWireBus, OneWireBus::NoDevice);
    }

    Device& DeviceManager::createOneWireDevice(OneWireBus & oneWireBus, OneWireBus::Address address)
    {
        OneWireDevice* device = new OneWireDevice(oneWireBus, address);
        this->registeredDevices[this->currentIndex++] = device;
        return *device;
    }

    Device& DeviceManager::createSPIDevice(SPIBus & spiBus)
    {
        return this->createSPIDevice(spiBus, dummyGpio);
    }

    Device& DeviceManager::createSPIDevice(SPIBus & spiBus, Gpio & csPin)
    {
        SPIDevice* device = new SPIDevice(spiBus, csPin);
        this->registeredDevices[this->currentIndex++] = device;
        return *device;
    }

    Device& DeviceManager::createUARTDevice(UARTPort & uartPort)
    {
        UARTDevice* device = new UARTDevice(uartPort);
        this->registeredDevices[this->currentIndex++] = device;
        return *device;
    }
}