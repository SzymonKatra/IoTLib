#pragma once

#include <driver/gpio.h>
#include <driver/i2c.h>

namespace iotlib
{
    namespace esp8266
    {
        typedef gpio_num_t GpioPinDefinition;
        const GpioPinDefinition GPIO0 = GPIO_NUM_0;
        const GpioPinDefinition GPIO1 = GPIO_NUM_1;
        const GpioPinDefinition GPIO2 = GPIO_NUM_2;
        const GpioPinDefinition GPIO3 = GPIO_NUM_3;
        const GpioPinDefinition GPIO4 = GPIO_NUM_4;
        const GpioPinDefinition GPIO5 = GPIO_NUM_5;
        const GpioPinDefinition GPIO6 = GPIO_NUM_6;
        const GpioPinDefinition GPIO7 = GPIO_NUM_7;
        const GpioPinDefinition GPIO8 = GPIO_NUM_8;
        const GpioPinDefinition GPIO9 = GPIO_NUM_9;
        const GpioPinDefinition GPIO10 = GPIO_NUM_10;
        const GpioPinDefinition GPIO11 = GPIO_NUM_11;
        const GpioPinDefinition GPIO12 = GPIO_NUM_12;
        const GpioPinDefinition GPIO13 = GPIO_NUM_13;
        const GpioPinDefinition GPIO14 = GPIO_NUM_14;
        const GpioPinDefinition GPIO15 = GPIO_NUM_15;
        const GpioPinDefinition GPIO16 = GPIO_NUM_16;

        typedef i2c_port_t I2CBusDefinition;
        const I2CBusDefinition I2C_Bus0 = I2C_NUM_0;

        typedef gpio_num_t I2CSdaPinDefinition;
        const I2CSdaPinDefinition I2C_SDA_GPIO4 = GPIO_NUM_4;

        typedef GpioPinDefinition I2CSclPinDefinition;
        const I2CSdaPinDefinition I2C_SCL_GPIO5 = GPIO_NUM_5;
    }

    typedef esp8266::GpioPinDefinition GpioPinDefinition;
    typedef esp8266::I2CBusDefinition I2CBusDefinition;
    typedef esp8266::I2CSdaPinDefinition I2CSdaPinDefinition;
    typedef esp8266::I2CSclPinDefinition I2CSclPinDefinition;
}
