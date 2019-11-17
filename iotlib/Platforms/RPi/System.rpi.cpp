#include "System.rpi.hpp"
#include <stdio.h>
#include <unistd.h>
#include "bcm2835.h"

namespace iotlib
{
    void System::initialize()
    {
        bcm2835_init();
    }
    void System::finalize()
    {
        bcm2835_close();
    }

    void System::sleep(uint32_t milliseconds)
    {
        bcm2835_delay(milliseconds);
    }

    void System::waitUs(uint32_t microseconds)
    {
        bcm2835_delayMicroseconds(microseconds);
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
