# IoTLib

Prototype of multiplatform library for embedded systems that allows writing portable code for handling sensors and other external peripherals.

Supported platforms:
- [ESP8266](https://www.espressif.com/en/products/socs/esp8266)
- [Raspberry Pi](https://www.raspberrypi.org/)

Supported peripherals:
- Humidity, barometric and temperature sensor [BME280](https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/)
- Digital temperature sensor **DS18B20**
- LCD controller [HD44780](https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller)
- Analog temperature sensor [MCP9700](https://www.microchip.com/en-us/product/mcp9700)
- Smog sensor [PMS3003](https://www.plantower.com/en/products_33/73.html)

## Example usage

```
(...)

int main()
{
    // Hardware
    iotlib::I2CBus i2c(app::I2CBus, app::I2CBus_SDA, app::I2CBus_SCL);
    iotlib::OneWireBus oneWire(app::OneWireBus);
    iotlib::UARTPort uart(app::UARTPort, 9600, iotlib::UARTPort::Parity::None, iotlib::UARTPort::StopBits::One);
    iotlib::Gpio io0(app::IO0, iotlib::Gpio::Direction::Output);

    // Device manager
    iotlib::DeviceManager deviceManager;

    // Drivers
    iotlib::HD44780 lcd(deviceManager.createI2CDevice(i2c, app::HD44780_ADDRESS));
    iotlib::DS18B20 tempProbe(deviceManager.createOneWireDevice(oneWire));
    iotlib::BME280 weatherSensor(deviceManager.createI2CDevice(i2c, app::BME280_ADDRESS));
    iotlib::PMS3003 smogSensor(deviceManager.createUARTDevice(uart));
    iotlib::Device& ledDevice = deviceManager.createGpioDevice(io0);

    tempProbe.startConversion();

    lcd.text(" *** IoTLib *** ");
    lcd.cursorGoTo(0, 1);
    lcd.text("  multiplatform ");
    iotlib::System::sleep(2000);

    char buffer[8][17];
    uint8_t scroll = 0;
    while (true)
    {
        ledDevice.write(ledDevice.read() == 0 ? 1 : 0);

        int8_t probeTemp;
        iotlib::BME280::Result weatherResult;
        iotlib::PMS3003::Data smogResult;

        probeTemp = tempProbe.readIntTemperature();
        weatherSensor.getData(weatherResult);
        smogSensor.read(smogResult);

        tempProbe.startConversion();

        uint8_t line = 0;
        sprintf(buffer[line++], "Temp: %d \xDF""C", probeTemp);
        *buffer[line++] = 0;
        sprintf(buffer[line++], "Temp: %d \xDF""C", weatherResult.Temperature / 100);
        sprintf(buffer[line++], "Humid: %d%%", weatherResult.Humidity / 1024);
        sprintf(buffer[line++], "%d hPa", weatherResult.Pressure / (100 * 100));
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
```

## Source code
- `iotlib` directory - source code of the library,
- `examples` directory - source code of example applications. 

## Usage

### Raspberry Pi
Requirements:
- gcc, make, cmake

1. Clone repository
2. `cd examples/rpi_wip/`
3. `configure.sh`
4.  cd build/Debug` or `cd build/Relase` and use `make` to compile the project.

### ESP8266
Requirements: 
- PC with Linux based OS
- ESP8266 RTOS SDK, to be installed from https://github.com/espressif/ESP8266_RTOS_SDK
- make

1. Clone repository
2. `cd examples/esp8266_wip`
3. Connect ESP8266 board to PC (it must have built-it USB-UART converted, otherwise please use external one)
4. `make menuconfig` and select serial port where your board is connected,
5. `make app-flash`. Example project will be built and uploaded to the board.

## References 

- Microchip Technology Inc., Hardware Abstraction Layer - http://ww1.microchip.com/downloads/en/DeviceDoc/hardware-abstraction-layer.pdf
- Jacob Beningo, 10 Tips for designing a HAL - https://www.edn.com/electronics-blogs/embedded-basics/4439613/10-Tips-for-designing-a-HAL
- Łukasz Krzak, Hardware abstraction layer for microcontrollers - http://home.agh.edu.pl/~lkrzak/hal/hal_idea.pdf
- Espressif, ESP8266 Technical Reference - https://www.espressif.com/sites/default/files/documentation/esp8266-technical_reference_en.pdf
- Raspberry Pi Foundation, Raspberry Pi Documentation - https://www.raspberrypi.org/documentation/
- Adafruit, datasheets
http://www.adafruit.com/datasheets/MCP9808.pdf
http://www.adafruit.com/datasheets/BST-BME280_DS001-10.pdf
http://www.adafruit.com/datasheets/MPR121.pdf
- Hitachi, HD44780U datasheet - https://www.sparkfun.com/datasheets/LCD/HD44780.pdf
