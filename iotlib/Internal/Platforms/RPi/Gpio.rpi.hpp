#pragma once

#include "bcm2835.h"

namespace iotlib
{
    namespace rpi
    {
        typedef RPiGPIOPin GpioPinDefinition;

        const GpioPinDefinition GPIO_NONE = (GpioPinDefinition)0x7FFFFFFF;

        const GpioPinDefinition GPIO2 = RPI_BPLUS_GPIO_J8_03;
        const GpioPinDefinition GPIO3 = RPI_BPLUS_GPIO_J8_05;
        const GpioPinDefinition GPIO4 = RPI_BPLUS_GPIO_J8_07;
        const GpioPinDefinition GPIO14 = RPI_BPLUS_GPIO_J8_08;
        const GpioPinDefinition GPIO15 = RPI_BPLUS_GPIO_J8_10;
        const GpioPinDefinition GPIO17 = RPI_BPLUS_GPIO_J8_11;
        const GpioPinDefinition GPIO18 = RPI_BPLUS_GPIO_J8_12;
        const GpioPinDefinition GPIO27 = RPI_BPLUS_GPIO_J8_13;
        const GpioPinDefinition GPIO22 = RPI_BPLUS_GPIO_J8_15;
        const GpioPinDefinition GPIO23 = RPI_BPLUS_GPIO_J8_16;
        const GpioPinDefinition GPIO24 = RPI_BPLUS_GPIO_J8_18;
        const GpioPinDefinition GPIO10 = RPI_BPLUS_GPIO_J8_19;
        const GpioPinDefinition GPIO9 = RPI_BPLUS_GPIO_J8_21;
        const GpioPinDefinition GPIO25 = RPI_BPLUS_GPIO_J8_22;
        const GpioPinDefinition GPIO11 = RPI_BPLUS_GPIO_J8_23;
        const GpioPinDefinition GPIO8 = RPI_BPLUS_GPIO_J8_24;
        const GpioPinDefinition GPIO7 = RPI_BPLUS_GPIO_J8_26;
        const GpioPinDefinition GPIO5 = RPI_BPLUS_GPIO_J8_29;
        const GpioPinDefinition GPIO6 = RPI_BPLUS_GPIO_J8_31;
        const GpioPinDefinition GPIO12 = RPI_BPLUS_GPIO_J8_32;
        const GpioPinDefinition GPIO13 = RPI_BPLUS_GPIO_J8_33;
        const GpioPinDefinition GPIO19 = RPI_BPLUS_GPIO_J8_35;
        const GpioPinDefinition GPIO16 = RPI_BPLUS_GPIO_J8_36;
        const GpioPinDefinition GPIO26 = RPI_BPLUS_GPIO_J8_37;
        const GpioPinDefinition GPIO20 = RPI_BPLUS_GPIO_J8_38;
        const GpioPinDefinition GPIO21 = RPI_BPLUS_GPIO_J8_40;
    }

    typedef rpi::GpioPinDefinition GpioPinDefinition;

    class Gpio
    {
    public:
        enum class Direction {
            Input,
            Output,
            OutputOpenDrain
        };

    private:
        iotlib::GpioPinDefinition pin;
        Direction direction;

    public:
        Gpio(iotlib::GpioPinDefinition, iotlib::Gpio::Direction direction);
        Gpio(iotlib::GpioPinDefinition, iotlib::Gpio::Direction direction, bool initValue);
        ~Gpio();

        void write(bool value);
        bool read();

        static Gpio createDummy();

        bcm2835FunctionSelect convertDirection(Direction direction);
    };
}
