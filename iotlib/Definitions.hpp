#pragma once

#if defined(IOTLIB_ESP8266)
    #include "Platform/Esp8266/Definitions.esp8266.hpp"
#elif defined(IOTLIB_RPI)
    #include "Platform/RPi/Definitions.rpi.hpp"
#elif defined(IOTLIB_MOCK)
    #include "Platform/Mock/Definitions.mock.hpp"
#else
    #error "Platform is not selected"
#endif