#include "MCP9700.hpp"

namespace iotlib
{
    MCP9700::MCP9700(Device& device)
        : device(device)
    {
    }

    MCP9700::~MCP9700()
    {
    }

    int8_t MCP9700::readTemperature()
    {
        uint16_t milivolts;
        this->device.read(&milivolts, 2);

        if (milivolts < 100) return -40;
        else if (milivolts > 1750) return 125;

        uint16_t degress = (milivolts - 100) / 10;
        return -40 + degress;
    }
}