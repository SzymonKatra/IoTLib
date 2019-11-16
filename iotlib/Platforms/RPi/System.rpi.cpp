#include "System.rpi.hpp"
#include <stdio.h>
#include <unistd.h>

namespace iotlib
{
    void System::sleep(uint32_t milliseconds)
    {
        usleep(milliseconds * 1000);
        /*struct timespec ts;
        int res;

        ts.tv_sec = milliseconds / 1000;
        ts.tv_nsec = (milliseconds % 1000) * 1000000;

        do {
            res = nanosleep(&ts, &ts);
        } while (res && errno == EINTR);*/
    }

    void System::waitUs(uint32_t microseconds)
    {
        usleep(microseconds);
    }

    void System::error(const char* str)
    {
        fprintf(stderr, str);
    }

    void System::enterCritical()
    {
        // TODO
    }

    void System::leaveCritical()
    {
        // TODO
    }
}
