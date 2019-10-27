#include "System.esp8266.hpp"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

namespace iotlib
{
    void System::delay(uint32_t milliseconds)
    {
        vTaskDelay(milliseconds / portTICK_PERIOD_MS);
    }

    void System::error(const char* str)
    {
        ESP_LOGE("IoTLib", str);
    }
}