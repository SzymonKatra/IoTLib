#pragma once

#include "Device.hpp"
#include "Hardware/Gpio.hpp"
#include "Hardware/Adc.hpp"
#include "Hardware/I2CBus.hpp"
#include "Hardware/SPIBus.hpp"
#include "Hardware/UARTPort.hpp"
#include "Hardware/OneWireBus.hpp"

namespace iotlib
{
    class DeviceManager
    {
    private:
        Device* registeredDevices[32];
        size_t currentIndex;
        Gpio dummyGpio;

    public:
        DeviceManager();
        ~DeviceManager();

        Device& createAdcDevice(Adc& adc);
        Device& createGpioDevice(Gpio& gpio);
        Device& createI2CDevice(I2CBus& i2cBus, uint8_t address);
        Device& createOneWireDevice(OneWireBus& oneWireBus);
        Device& createOneWireDevice(OneWireBus& oneWireBus, OneWireBus::Address address);
        Device& createSPIDevice(SPIBus& spiBus);
        Device& createSPIDevice(SPIBus& spiBus, Gpio& csPin);
        Device& createUARTDevice(UARTPort& uartPort);
    };
}