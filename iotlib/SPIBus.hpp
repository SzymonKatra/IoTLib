#pragma once

#if defined(IOTLIB_ESP8266)
    #include "Internal/Platforms/Esp8266/SPIBus.esp8266.hpp"
#elif defined(IOTLIB_RPI)
    #include "Internal/Platforms/RPi/SPIBus.rpi.hpp"
#else
    #error "Platform is not selected"
#endif