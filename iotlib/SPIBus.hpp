#pragma once

#if defined(IOTLIB_ESP8266)
    #include "Platforms/Esp8266/SPIBus.esp8266.hpp"
#elif defined(IOTLIB_RPI)
    #include "Platforms/RPi/SPIBus.rpi.hpp"
#elif defined(IOTLIB_MOCK)
    #include "Platforms/Mock/SPIBus.mock.hpp"
#else
    #error "Platform is not selected"
#endif