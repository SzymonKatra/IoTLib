# IoTLib

Prototype of multiplatform library for embedded systems that allows to write portable code for handling sensors and other external peripherals.

Supported platforms:
- [ESP8266](https://www.espressif.com/en/products/socs/esp8266)
- [Raspberry Pi](https://www.raspberrypi.org/)

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
