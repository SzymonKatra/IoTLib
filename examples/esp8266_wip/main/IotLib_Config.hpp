#pragma once

#include <iotlib/IoTLib.hpp>

namespace app {
    const iotlib::GpioPinDefinition LedA = iotlib::esp8266::GPIO2;
    const iotlib::UARTPortDefinition Debug = iotlib::esp8266::UART_Port0;
}
