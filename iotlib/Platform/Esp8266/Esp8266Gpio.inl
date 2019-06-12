#include <driver/gpio.h>

namespace iotlib {
    namespace platform {
        void gpioSetupIn(iotlib::GpioPinDefinition pin) {
            gpio_config_t io_conf;
            io_conf.intr_type = GPIO_INTR_DISABLE;
            io_conf.mode = GPIO_MODE_INPUT;
            io_conf.pin_bit_mask = (1 << pin);
            io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
            io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
            gpio_config(&io_conf);
        }

        void gpioSetupOut(iotlib::GpioPinDefinition pin) {
            gpio_config_t io_conf;
            io_conf.intr_type = GPIO_INTR_DISABLE;
            io_conf.mode = GPIO_MODE_OUTPUT;
            io_conf.pin_bit_mask = (1 << pin);
            io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
            io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
            gpio_config(&io_conf);
        }

        void gpioWriteHigh(iotlib::GpioPinDefinition pin) {
            gpio_set_level(pin, 1);
        }

        void gpioWriteLow(iotlib::GpioPinDefinition pin) {
            gpio_set_level(pin, 0);
        }

        bool gpioRead(iotlib::GpioPinDefinition pin) {
            return gpio_get_level(pin) > 0;
        }
    }
}