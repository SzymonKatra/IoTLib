#include <stdio.h>

#include "esp_system.h"
#include "IotLib_Config.hpp"
#include <iotlib/IoTLib.hpp>

extern "C" {
    void app_main(void)
    {
        printf("HELLO ESP SDK version:%s\n", esp_get_idf_version());
        iotlib::Gpio::setup(app::LedA, iotlib::Gpio::Direction::Output);
        iotlib::Gpio::write(app::LedA, false);
    }
}
