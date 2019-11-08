#pragma once

#include <stdint.h>

namespace iotlib
{
    class System
    {
    public:
        static void sleep(uint32_t milliseconds);
        static void waitUs(uint32_t microseconds);
        static void error(const char* str);
    };
}