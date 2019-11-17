#pragma once

#if defined(IOTLIB_ESP8266)
    #include "Internal/Platforms/Esp8266/Library.esp8266.hpp"
#elif defined(IOTLIB_RPI)
    #include "Internal/Platforms/RPi/Library.rpi.hpp"
#else
    #error "Platform is not selected"
#endif