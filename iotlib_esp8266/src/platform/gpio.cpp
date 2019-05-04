#include <iotlib/platform/gpio.hpp>

#include <driver/gpio.h>

namespace iotlib {
    namespace platform {
        void gpio_setup_in(iotlib::GpioPinDefinition pin) {
            gpio_config_t io_conf;
            io_conf.intr_type = GPIO_INTR_DISABLE;
            io_conf.mode = GPIO_MODE_INPUT;
            io_conf.pin_bit_mask = (1 << pin);
            io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
            io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
            gpio_config(&io_conf);
        }

        void gpio_setup_out(iotlib::GpioPinDefinition pin) {
            gpio_config_t io_conf;
            io_conf.intr_type = GPIO_INTR_DISABLE;
            io_conf.mode = GPIO_MODE_OUTPUT;
            io_conf.pin_bit_mask = (1 << pin);
            io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
            io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
            gpio_config(&io_conf);
        }

        void gpio_write_high(iotlib::GpioPinDefinition pin) {
            gpio_set_level(pin, 1);
        }

        void gpio_write_low(iotlib::GpioPinDefinition pin) {
            gpio_set_level(pin, 0);
        }

        bool gpio_read(iotlib::GpioPinDefinition pin) {
            return true;
        }
    }
}