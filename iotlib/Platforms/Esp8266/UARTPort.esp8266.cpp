#include "UARTPort.esp8266.hpp"
#include <string.h>

namespace iotlib
{
    UARTPort::UARTPort(UARTPortDefinition port, uint32_t baudRate, UARTPort::Parity parity, UARTPort::StopBits stopBits)
    {
        if (port == esp8266::UART_Port0Swapped)
        {
            port = esp8266::UART_Port0;
            uart_enable_swap();
            this->isUART0Swapped = true;
        }

        this->port = port;

        uart_config_t config;
        config.baud_rate = baudRate;
        config.parity = this->convertParity(parity);
        config.stop_bits = this->convertStopBits(stopBits);
        config.data_bits = UART_DATA_8_BITS;
        config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;

        uart_param_config(port, &config);
        uart_driver_install(port, UART_FIFO_LEN * 2, 0, 0, NULL);
    }
    UARTPort::~UARTPort()
    {
        uart_driver_delete(this->port);
        if (this->isUART0Swapped)
        {
            uart_disable_swap();
        }

        if (port == esp8266::UART_Port0)
        {
            uart_config_t config;
            config.baud_rate = 74880;
            config.parity = UART_PARITY_DISABLE;
            config.stop_bits = UART_STOP_BITS_1;
            config.data_bits = UART_DATA_8_BITS;
            config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
            uart_param_config(port, &config);
        }
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
        this->write((const uint8_t*)str, strlen(str));
    }

    uart_parity_t UARTPort::convertParity(UARTPort::Parity parity)
    {
        switch (parity)
        {
        case UARTPort::Parity::None: return UART_PARITY_DISABLE;
        case UARTPort::Parity::Even: return UART_PARITY_EVEN;
        case UARTPort::Parity::Odd: return UART_PARITY_ODD;
        default: return UART_PARITY_DISABLE;
        }
    }

    uart_stop_bits_t UARTPort::convertStopBits(UARTPort::StopBits stopBits)
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