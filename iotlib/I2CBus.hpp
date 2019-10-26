#pragma once

#if defined(IOTLIB_ESP8266)
    #include "Platforms/Esp8266/I2CBus.esp8266.hpp"
#elif defined(IOTLIB_RPI)
    #include "Platforms/RPi/I2CBus.rpi.hpp"
#elif defined(IOTLIB_MOCK)
    #include "Platforms/Mock/I2CBus.mock.hpp"
#else
    #error "Platform is not selected"
#endif