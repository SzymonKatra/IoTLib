#pragma once

#include <stdint.h>

namespace iotlib
{
    class System
    {
    public:
        static void delay(uint32_t milliseconds);
        static void error(const char* str);
    };
}