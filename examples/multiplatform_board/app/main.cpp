#include <stdlib.h>
#include <iotlib/IoTLib.hpp>
#include <iotlib/Devices/HD44780.hpp>
#include <iotlib/Devices/BME280.hpp>
#include <iotlib/Devices/DS18B20.hpp>
#include <iotlib/Devices/PMS3003.hpp>
#include "config.hpp"

int main()
{
    iotlib::I2CBus i2c(app::I2CBus, app::I2CBus_SDA, app::I2CBus_SCL);
    iotlib::OneWireBus oneWire(app::OneWireBus);
    //iotlib::UARTPort uart(app::UARTPort, 9600, iotlib::UARTPort::Parity::None, iotlib::UARTPort::StopBits::One);

    iotlib::HD44780 lcd(i2c, app::HD44780_ADDRESS);
    lcd.text(" *** IoTLib *** ");
    lcd.cursorGoTo(0, 1);
    lcd.text("  multiplatform ");

    iotlib::OneWireBus::Address oneWireAddresses[3];
    size_t tempSensorsCount = oneWire.search(iotlib::OneWireBus::SearchType::SearchRom, oneWireAddresses, 3);

    iotlib::DS18B20::allStartConversion(oneWire);
    iotlib::System::sleep(2000);

    char buffer[5][17];
    while (true)
    {
        lcd.clear();
        uint8_t line = 0;

        for (size_t i = 0; i < tempSensorsCount; i++)
        {
            iotlib::DS18B20 tempSensor(oneWire, oneWireAddresses[i]);
            sprintf(buffer[line], "T%d: %d \xDF""C", i + 1, tempSensor.readIntTemperature());
            line++;
        }

        lcd.clear();
        lcd.text(buffer[0]);
        lcd.cursorGoTo(0, 1);
        lcd.text(buffer[1]);
        iotlib::System::sleep(1000);

        iotlib::DS18B20::allStartConversion(oneWire);
    }
}