#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "Gpio.hpp"
#include "Adc.hpp"
#include "I2CBus.hpp"
#include "SPIBus.hpp"
#include "UARTPort.hpp"
#include "OneWireBus.hpp"

namespace iotlib
{
    class Device
    {
    public:
        virtual size_t write(const void* data, size_t length) = 0;
        void write(uint8_t data);

        virtual size_t read(void* data, size_t length) = 0;
        uint8_t read();
    };

    class GpioDevice : public Device
    {
    private:
        Gpio& gpio;

    public:
        GpioDevice(Gpio& gpio);

        virtual size_t write(const void* data, size_t length);
        virtual size_t read(void* data, size_t length);
    };

    class AdcDevice : public Device
    {
    private:
        Adc& adc;

    public:
        AdcDevice(Adc& adc);

        virtual size_t write(const void* data, size_t length);
        virtual size_t read(void* data, size_t length);
    };

    class I2CDevice : public Device
    {
    private:
        I2CBus& i2cBus;
        uint8_t address;

    public:
        I2CDevice(I2CBus& i2cBus, uint8_t address);

        virtual size_t write(const void* data, size_t length);
        virtual size_t read(void* data, size_t length);
    };

    class SPIDevice : public Device
    {
    private:
        SPIBus& spiBus;

    public:
        SPIDevice(SPIBus& spiBus);

        virtual size_t write(const void* data, size_t length);
        virtual size_t read(void* data, size_t length);
    };

    class UARTDevice : public Device
    {
    private:
        UARTPort& uartPort;

    public:
        UARTDevice(UARTPort& uartPort);

        virtual size_t write(const void* data, size_t length);
        virtual size_t read(void* data, size_t length);
    };

    class OneWireDevice : public Device
    {
    private:
        OneWireBus& oneWireBus;
        OneWireBus::Address address;

    public:
        OneWireDevice(OneWireBus& oneWireBus);
        OneWireDevice(OneWireBus& oneWireBus, OneWireBus::Address address);

        virtual size_t write(const void* data, size_t length);
        virtual size_t read(void* data, size_t length);

    private:
        void selectDevice();
    };
}