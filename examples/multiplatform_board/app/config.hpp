#include <iotlib/IoTLib.hpp>

namespace app
{
#ifdef IOTLIB_ESP8266

    const iotlib::I2CBusDefinition I2CBus = iotlib::esp8266::I2C_Bus0;
    const iotlib::I2CSclPinDefinition I2CBus_SCL = iotlib::esp8266::I2C_SCL_GPIO5;
    const iotlib::I2CSclPinDefinition I2CBus_SDA = iotlib::esp8266::I2C_SDA_GPIO4;

    const iotlib::SPIBusDefinition SPIBus = iotlib::esp8266::SPI_BusHSPI;

    const iotlib::OneWireBusDefinition OneWireBus = iotlib::esp8266::GPIO16;

    const iotlib::UARTPortDefinition UARTPort = iotlib::esp8266::UART_Port0Swapped;

    const iotlib::AdcPinDefinition ADC = iotlib::esp8266::ADC_TOUT;

    const iotlib::GpioPinDefinition IO0 = iotlib::esp8266::GPIO0;
    const iotlib::GpioPinDefinition IO1 = iotlib::esp8266::GPIO2;
    const iotlib::GpioPinDefinition IO2 = iotlib::esp8266::GPIO9;
    const iotlib::GpioPinDefinition IO3 = iotlib::esp8266::GPIO10;

#elif IOTLIB_RPI

    const iotlib::I2CBusDefinition I2CBus = iotlib::rpi::I2C_Bus0;
    const iotlib::I2CSclPinDefinition I2CBus_SCL = iotlib::rpi::I2C_SCL_GPIO3;
    const iotlib::I2CSclPinDefinition I2CBus_SDA = iotlib::rpi::I2C_SDA_GPIO2;

    const iotlib::SPIBusDefinition SPIBus = iotlib::rpi::SPI_Bus0;

    const iotlib::OneWireBusDefinition OneWireBus = iotlib::rpi::GPIO4;

    const iotlib::UARTPortDefinition UARTPort = iotlib::rpi::UART_Primary;

    const iotlib::AdcPinDefinition ADC = iotlib::rpi::ADC_NONE;

    const iotlib::GpioPinDefinition IO0 = iotlib::rpi::GPIO6;
    const iotlib::GpioPinDefinition IO1 = iotlib::rpi::GPIO13;
    const iotlib::GpioPinDefinition IO2 = iotlib::rpi::GPIO19;
    const iotlib::GpioPinDefinition IO3 = iotlib::rpi::GPIO26;

#else
    #error Platform not selected
#endif

    const uint8_t HD44780_ADDRESS = 0x27;
    const uint8_t BME280_ADDRESS = 0x76;
}