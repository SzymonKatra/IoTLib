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