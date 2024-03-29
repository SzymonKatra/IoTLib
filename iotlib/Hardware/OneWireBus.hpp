#pragma once

#if defined(IOTLIB_ESP8266)
    #include "../Internal/Platforms/Generic/OneWireBus.generic.hpp"
#elif defined(IOTLIB_RPI)
    #include "../Internal/Platforms/Generic/OneWireBus.generic.hpp"
#else
    #error "Platform is not selected"
#endif