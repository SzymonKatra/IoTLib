#include "System.esp8266.hpp"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <rom/ets_sys.h>

namespace iotlib
{
    void System::initialize()
    {
    }
    void System::finalize()
    {
    }

    void System::sleep(uint32_t milliseconds)
    {
        vTaskDelay(milliseconds / portTICK_PERIOD_MS);
    }

    void System::waitUs(uint32_t microseconds)
    {
        ets_delay_us(microseconds);
    }

    void System::error(const char* str)
    {
        ESP_LOGE("IoTLib", str);
    }

    void System::enterCritical()
    {
        taskENTER_CRITICAL();
    }

    void System::leaveCritical()
    {
        taskEXIT_CRITICAL();
    }
}