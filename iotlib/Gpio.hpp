#pragma once

#if defined(IOTLIB_ESP8266)
    #include "Platforms/Esp8266/Gpio.esp8266.hpp"
#elif defined(IOTLIB_RPI)
    #include "Platforms/RPi/Gpio.rpi.hpp"
#elif defined(IOTLIB_MOCK)
    #include "Platforms/Mock/Gpio.mock.hpp"
#else
    #error "Platform is not selected"
#endif