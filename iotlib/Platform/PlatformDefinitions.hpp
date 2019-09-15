#pragma once

#if defined(IOTLIB_ESP8266)
    #include "Esp8266/Esp8266Definitions.hpp"
#elif defined(IOTLIB_RPI)
    #include "RPi/RPiDefinitions.hpp"
#elif defined(IOTLIB_MOCK)
    #include "Mock/MockDefinitions.hpp"
#else
    #error "Platform is not selected"
#endif

namespace iotlib {
    #if defined(IOTLIB_ESP8266)
        typedef esp8266::GpioPinDefinition GpioPinDefinition;
        typedef esp8266::I2CBusDefinition I2CBusDefinition;
        typedef esp8266::I2CSdaPinDefinition I2CSdaPinDefinition;
        typedef esp8266::I2CSclPinDefinition I2CSclPinDefinition;

    #elif defined(IOTLIB_RPI)
        typedef rpi::GpioPinDefinition GpioPinDefinition;

    #elif defined(IOTLIB_MOCK)
        typedef mock::GpioPinDefinition GpioPinDefinition;

    #else
        #error "Platform is not selected"
    #endif
}
