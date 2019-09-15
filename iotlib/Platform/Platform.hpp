#pragma once

#include "PlatformDefinitions.hpp"
#include <stdint.h>

namespace iotlib {
    namespace platform {
        void gpioSetupIn(iotlib::GpioPinDefinition pin);
        void gpioSetupOut(iotlib::GpioPinDefinition pin);
        void gpioWriteHigh(iotlib::GpioPinDefinition pin);
        void gpioWriteLow(iotlib::GpioPinDefinition pin);
        bool gpioRead(iotlib::GpioPinDefinition pin);


        void i2cSetup(iotlib::I2CBusDefinition bus, iotlib::I2CSdaPinDefinition sdaPin, iotlib::I2CSclPinDefinition sclPin);
        void i2cWrite(iotlib::I2CBusDefinition bus, const uint8_t* data, size_t length);
        void i2cRead(iotlib::I2CBusDefinition bus, uint8_t data, size_t length);
    }
}