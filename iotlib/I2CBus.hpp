#pragma once

#include <cstdint>
#include "Definitions.hpp"

namespace iotlib
{
    class I2CBus {
    private:
        iotlib::I2CBusDefinition bus;

    public:
        I2CBus(iotlib::I2CSdaPinDefinition sdaPin, iotlib::I2CSclPinDefinition sclPin);
        ~I2CBus();
        
        void write(std::uint8_t address, const std::uint8_t* data, std::size_t length);
        void read(std::uint8_t address, std::uint8_t* data, std::size_t length);
    };
}