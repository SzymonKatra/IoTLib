#include "Platform.hpp"

namespace iotlib {
    namespace platform {
        #if defined(IOTLIB_ESP8266)
            #include "Esp8266/Esp8266PlatformImpl.inl"
        #elif defined(IOTLIB_RPI)
            #include "RPi/RPiPlatformImpl.inl"
        #elif defined(IOTLIB_MOCK)
            #include "Mock/MockPlatformImpl.inl"
        #else
            #error Platform is not selected
        #endif
    }
}