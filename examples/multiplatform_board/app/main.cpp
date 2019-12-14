#include <stdlib.h>
#include <stdio.h>
#include <iotlib/IoTLib.hpp>
#include <iotlib/Drivers/HD44780.hpp>
#include <iotlib/Drivers/BME280.hpp>
#include <iotlib/Drivers/DS18B20.hpp>
#include <iotlib/Drivers/PMS3003.hpp>
#include "config.hpp"

#include <iotlib/Device.hpp>

int main()
{
    iotlib::I2CBus i2c(app::I2CBus, app::I2CBus_SDA, app::I2CBus_SCL);
    iotlib::OneWireBus oneWire(app::OneWireBus);
    //iotlib::UARTPort uart(app::UARTPort, 9600, iotlib::UARTPort::Parity::None, iotlib::UARTPort::StopBits::One);

    iotlib::I2CDevice lcdDevice(i2c, app::HD44780_ADDRESS);
    iotlib::OneWireDevice tempProbeDevice(oneWire);
    iotlib::I2CDevice weatherSensorDevice(i2c, app::BME280_ADDRESS);
    //iotlib::UARTDevice smogSensorDevice(uart);

    iotlib::HD44780 lcd(lcdDevice);
    iotlib::DS18B20 tempProbe(tempProbeDevice);
    iotlib::BME280 weatherSensor(weatherSensorDevice);
    //iotlib::PMS3003 smogSensor(smogSensorDevice);

    tempProbe.startConversion();

    lcd.text(" *** IoTLib *** ");
    lcd.cursorGoTo(0, 1);
    lcd.text("  multiplatform ");
    iotlib::System::sleep(2000);

    char buffer[8][17];
    uint8_t scroll = 0;
    while (true)
    {
        int8_t probeTemp;
        iotlib::BME280::Result weatherResult;
        iotlib::PMS3003::Data smogResult;

        probeTemp = tempProbe.readIntTemperature();
        weatherSensor.getData(weatherResult);
        //smogSensor.read(smogResult);

        tempProbe.startConversion();

        uint8_t line = 0;
        sprintf(buffer[line++], "Sonda T: %d \xDF""C", probeTemp);
        *buffer[line++] = 0;
        sprintf(buffer[line++], "Temp: %d \xDF""C", weatherResult.Temperature / 100);
        sprintf(buffer[line++], "Wilg: %d%%", weatherResult.Humidity / 1024);
        sprintf(buffer[line++], "Cisn: %d hPa", weatherResult.Pressure / (100 * 100));
        sprintf(buffer[line++], "PM 1: %d", smogResult.PM1Outdoor);
        sprintf(buffer[line++], "PM 2.5: %d", smogResult.PM2_5Outdoor);
        sprintf(buffer[line++], "PM 10: %d", smogResult.PM10Outdoor);

        lcd.clear();
        lcd.text(buffer[scroll % 8]);
        lcd.cursorGoTo(0, 1);
        lcd.text(buffer[(scroll + 1) % 8]);

        scroll += 2;
        iotlib::System::sleep(1500);
    }
}
