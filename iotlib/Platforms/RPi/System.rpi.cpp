#include "System.esp8266.hpp"
#include <iostream>
#include <unistd.h>

namespace iotlib
{
    void System::delay(uint32_t milliseconds)
    {
        struct timespec ts;
        int res;

        ts.tv_sec = milliseconds / 1000;
        ts.tv_nsec = (milliseconds % 1000) * 1000000;

        do {
            res = nanosleep(&ts, &ts);
        } while (res && errno == EINTR);

        return res;
    }

    void System::error(const char* str)
    {
        std::cerr << str << std::endl;
    }
}