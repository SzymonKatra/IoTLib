#include "Definitions.esp8266.hpp"
#include <driver/uart.h>
#include "../../UARTPort.hpp"
#include <string.h>

namespace iotlib
{
    namespace esp8266
    {
        namespace internal
        {
            static uart_parity_t toEsp8266(UARTPort::Parity parity)
            {
                switch (parity)
                {
                case UARTPort::Parity::None: return UART_PARITY_DISABLE;
                case UARTPort::Parity::Even: return UART_PARITY_EVEN;
                case UARTPort::Parity::Odd: return UART_PARITY_ODD;
                default: return UART_PARITY_DISABLE;
                }
            }

            static uart_stop_bits_t toEsp8266(UARTPort::StopBits stopBits)
            {
                switch (stopBits)
                {
                case UARTPort::StopBits::One: return UART_STOP_BITS_1;
                case UARTPort::StopBits::OneAndHalf: return UART_STOP_BITS_1_5;
                case UARTPort::StopBits::Two: return UART_STOP_BITS_2;
                default: return UART_STOP_BITS_MAX;
                }
            }
        }
        
    }

    UARTPort::UARTPort(UARTPortDefinition port, uint32_t baudRate, Parity parity, StopBits stopBits)
    {
        if (port == esp8266::UART_Port0Swapped)
        {
            port = esp8266::UART_Port0;
            uart_enable_swap();
        }
        else
        {
            uart_disable_swap();
        }

        this->port = port;

        uart_config_t config;
        config.baud_rate = baudRate;
        config.parity = esp8266::internal::toEsp8266(parity);
        config.stop_bits = esp8266::internal::toEsp8266(stopBits);
        config.data_bits = UART_DATA_8_BITS;
        config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;

        uart_param_config(port, &config);
        uart_driver_install(port, UART_FIFO_LEN * 2, 0, 0, NULL);
    }
    UARTPort::~UARTPort()
    {
        uart_driver_delete(this->port);
    }

    size_t UARTPort::write(const uint8_t* buffer, size_t size)
    {
        return uart_write_bytes(this->port, (const char*)buffer, size);
    }

    size_t UARTPort::read(uint8_t* buffer, size_t size)
    {
        return uart_read_bytes(this->port, buffer, size, 0);
    }

    void UARTPort::print(const char* str)
    {
        // no tx-buffer so write will block until everything is written
        this->write((const uint8_t*)str, strlen(str));
    }

    void UARTPort::println(const char* str)
    {
        this->print(str);
        this->print("\n");
    }
}