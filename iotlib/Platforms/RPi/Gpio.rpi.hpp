#pragma once

#include <driver/gpio.h>

namespace iotlib
{
    namespace rpi
    {
        typedef int GpioPinDefinition;

        const GpioPinDefinition GPIO0 = 0;
        const GpioPinDefinition GPIO1 = 1;
        const GpioPinDefinition GPIO2_SDA = 2;
        const GpioPinDefinition GPIO3_SCL = 3;
        const GpioPinDefinition GPIO4 = 4;
        const GpioPinDefinition GPIO5 = 5;
        const GpioPinDefinition GPIO6 = 6;
        const GpioPinDefinition GPIO7 = 7;
        const GpioPinDefinition GPIO8 = 8;
        const GpioPinDefinition GPIO9_MISO = 9;
        const GpioPinDefinition GPIO10_MOSI = 10;
        const GpioPinDefinition GPIO11_SCLK = 11;
        const GpioPinDefinition GPIO12 = 12;
        const GpioPinDefinition GPIO13 = 13;
        const GpioPinDefinition GPIO14_TX = 14;
        const GpioPinDefinition GPIO15_RX = 15;
        const GpioPinDefinition GPIO16 = 16;
        const GpioPinDefinition GPIO17 = 17;
        const GpioPinDefinition GPIO18 = 18;
        const GpioPinDefinition GPIO19 = 19;
        const GpioPinDefinition GPIO20 = 20;
        const GpioPinDefinition GPIO21 = 21;
        const GpioPinDefinition GPIO22 = 22;
        const GpioPinDefinition GPIO23 = 23;
        const GpioPinDefinition GPIO24 = 24;
        const GpioPinDefinition GPIO25 = 25;
        const GpioPinDefinition GPIO26 = 26;
        const GpioPinDefinition GPIO27 = 27;
        const GpioPinDefinition GPIO28 = 28;
        const GpioPinDefinition GPIO29 = 29;
        const GpioPinDefinition GPIO30 = 30;
        const GpioPinDefinition GPIO31 = 31;
        const GpioPinDefinition GPIO32 = 32;
        const GpioPinDefinition GPIO33 = 33;
        const GpioPinDefinition GPIO34 = 34;
        const GpioPinDefinition GPIO35 = 35;
        const GpioPinDefinition GPIO36 = 36;
        const GpioPinDefinition GPIO37 = 37;
        const GpioPinDefinition GPIO38 = 38;
        const GpioPinDefinition GPIO39 = 39;
        const GpioPinDefinition GPIO40 = 40;
        const GpioPinDefinition GPIO41 = 41;
        const GpioPinDefinition GPIO42 = 42;
        const GpioPinDefinition GPIO43 = 43;
        const GpioPinDefinition GPIO44 = 44;
        const GpioPinDefinition GPIO45 = 45;
        const GpioPinDefinition GPIO46 = 46;
        const GpioPinDefinition GPIO47 = 47;
        const GpioPinDefinition GPIO48 = 48;
        const GpioPinDefinition GPIO49 = 49;
        const GpioPinDefinition GPIO50 = 50;
        const GpioPinDefinition GPIO51 = 51;
        const GpioPinDefinition GPIO52 = 52;
        const GpioPinDefinition GPIO53 = 53;
    }

    typedef rpi::GpioPinDefinition GpioPinDefinition;

    class Gpio
    {
    public:
        enum class Direction {
            Input,
            Output
        };

        static void setup(iotlib::GpioPinDefinition pin, iotlib::Gpio::Direction direction);
        static void write(iotlib::GpioPinDefinition pin, bool value);
        static bool read(iotlib::GpioPinDefinition pin);
    };
}
