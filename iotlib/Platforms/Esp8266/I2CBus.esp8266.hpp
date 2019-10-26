#pragma once

#include <stdint.h>
#include <driver/i2c.h>
#include "Definitions.esp8266.hpp"

namespace iotlib
{
    // todo: error handling
    class I2CBus {
    private:
        iotlib::I2CBusDefinition bus;
        i2c_cmd_handle_t currentWriteCmd;
        bool currentWriteCheckAck;

    public:
        I2CBus(iotlib::I2CBusDefinition bus, iotlib::I2CSdaPinDefinition sdaPin, iotlib::I2CSclPinDefinition sclPin);
        ~I2CBus();

        void write(uint8_t address, const uint8_t* data, size_t length, bool checkAck = true);
        void read(uint8_t address, uint8_t* data, size_t length, bool checkAck = true);

        void beginWrite(uint8_t address, bool checkAck);
        void write(const uint8_t* data, size_t length);
        void endWrite();
    };
}