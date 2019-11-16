#pragma once

#if defined(IOTLIB_ESP8266)
    #include "Platforms/Generic/OneWireBus.generic.hpp"
#elif defined(IOTLIB_RPI)
    #include "Platforms/RPi/OneWireBus.rpi.hpp"
#else
    #error "Platform is not selected"
#endif