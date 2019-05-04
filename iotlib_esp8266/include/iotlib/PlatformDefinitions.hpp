#pragma once

// ESP8266 platform specific defines

#include <driver/gpio.h>

namespace iotlib {
    namespace platform {
        namespace esp8266 {
            typedef gpio_num_t GpioPinDefinition;

            const GpioPinDefinition GPIO2 = GPIO_NUM_2;
        }
    }

    typedef platform::esp8266::GpioPinDefinition GpioPinDefinition;
}
