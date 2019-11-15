#include "DS18B20.hpp"

namespace iotlib
{
    DS18B20::DS18B20(OneWireBus& bus)
        : DS18B20(bus, 0)
    {
    }

    DS18B20::DS18B20(OneWireBus& bus, uint64_t address)
        : bus(bus), address(address)
    {
    }

    DS18B20::~DS18B20()
    {

    }

    void DS18B20::startConversion()
    {
        this->selectDevice();
        this->bus.writeData<uint8_t>(0x44);
    }

    void DS18B20::setResolution(Resolution resolution)
    {
        this->writeScratchpad(0, 0, (uint8_t)resolution);
    }

    int16_t DS18B20::readRawTemperature()
    {
        this->selectDevice();
        this->bus.writeData<uint8_t>(0xBE);

        int16_t result = this->bus.readData<int16_t>();
        this->bus.reset();
        return result;
    }

    void DS18B20::selectDevice()
    {
        if (this->address != 0)
        {
            this->bus.matchRom(this->address);
        }
        else
        {
            this->bus.skipRom();
        }
    }

    void DS18B20::writeScratchpad(uint8_t th, uint8_t tl, uint8_t configReg)
    {
        this->selectDevice();
        this->bus.writeData<uint8_t>(0x4E);
        this->bus.writeData<uint8_t>(th);
        this->bus.writeData<uint8_t>(tl);
        this->bus.writeData<uint8_t>(configReg);
    }

    bool DS18B20::isAnyUsingParasitePower(OneWireBus& bus)
    {
        bus.skipRom();
        bus.writeData(0xB4);
        return !bus.read();
    }

    void DS18B20::allStartConversion(OneWireBus& bus)
    {
        bus.skipRom();
        bus.writeData<uint8_t>(0x44);
    }
}