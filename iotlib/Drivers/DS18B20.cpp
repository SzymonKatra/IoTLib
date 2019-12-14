#include "DS18B20.hpp"

namespace iotlib
{
    DS18B20::DS18B20(Device& device)
        : device(device)
    {
    }

    DS18B20::~DS18B20()
    {

    }

    void DS18B20::startConversion()
    {
        this->device.write(0x44);
    }

    void DS18B20::setResolution(Resolution resolution)
    {
        this->writeScratchpad(0, 0, (uint8_t)resolution);
    }

    int16_t DS18B20::readRawTemperature()
    {
        this->device.write(0xBE);

        int16_t result;
        this->device.read(&result, 2);

        return result;
    }

    int8_t DS18B20::readIntTemperature()
    {
        return this->readRawTemperature() >> 4;
    }


    void DS18B20::writeScratchpad(uint8_t th, uint8_t tl, uint8_t configReg)
    {
        this->device.write(0x4E);
        this->device.write(th);
        this->device.write(tl);
        this->device.write(configReg);
    }

    bool DS18B20::isAnyUsingParasitePower(OneWireBus& bus)
    {
        bus.skipRom();
        bus.writeData<uint8_t>(0xB4);
        return !bus.read();
    }

    void DS18B20::allStartConversion(OneWireBus& bus)
    {
        bus.skipRom();
        bus.writeData<uint8_t>(0x44);
    }
}