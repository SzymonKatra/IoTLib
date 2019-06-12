## Kompilacja i uruchomienie

### Ogólny opis
Źródła biblioteki znajdują się w katalogu `iotlib`. Przykładowe projekty są umieszczone w katalogu `examples`

### Raspberry Pi
Wymagania:
- gcc, make, cmake

1. Sklonować repozytorium
2. Przejść do katalogu `examples/rpi_wip/`
3. Uruchomić skrypt konfigurujący project `configure.sh`
4. Przejść do katalogu `build/Debug` lub `build/Relase` i użyć `make` w celu skompilowania projektu.

### ESP8266
Wymagania: 
- PC z systemem Linux
- ESP8266 RTOS SDK, do zainstalowania z https://github.com/espressif/ESP8266_RTOS_SDK
- make

1. Sklonować repozytorium
2. Przejść do katalogu `examples/esp8266_wip`
3. Podłączyć płytkę z ESP8266 do komputera (płytka musi mieć wbudowany konwerter USB-UART, w przeciwnym wypadku należy zastosować zewnętrzny)
4. Uruchomić polecenie `make menuconfig` i wybrać port szeregowy.
5. Uruchomić polecenie `make app-flash`. Przykładowy projekt zostanie zbudowany, a następnie wgrany na płytkę.

## Bibliografia 

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
