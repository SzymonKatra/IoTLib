#include "UARTPort.rpi.hpp"
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <stdio.h>

namespace iotlib
{
    UARTPort::UARTPort(UARTPortDefinition port, uint32_t baudRate, UARTPort::Parity parity, UARTPort::StopBits stopBits)
    {
        this->fd = open(port, O_RDWR);

        struct termios options;
        tcgetattr(fd, &options);
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS8;

        if (parity == UARTPort::Parity::None)
        {
            options.c_cflag &= ~PARENB;
        }
        else
        {
            options.c_cflag |= PARENB;
            if (parity == UARTPort::Parity::Odd)
            {
                options.c_cflag |= PARODD;
            }
            else
            {
                options.c_cflag &= ~PARODD;
            }
        }

        if (stopBits == UARTPort::StopBits::One)
        {
            options.c_cflag &= ~CSTOPB;
        }
        else
        {
            options.c_cflag |= CSTOPB;
        }

        cfsetspeed(&options, baudRate);
        tcsetattr(this->fd, 0, &options);
    }
    UARTPort::~UARTPort()
    {
        close(this->fd);
    }

    size_t UARTPort::write(const uint8_t* buffer, size_t size)
    {
        return ::write(this->fd, buffer, size);
    }

    size_t UARTPort::read(uint8_t* buffer, size_t size)
    {
        return ::read(this->fd, buffer, size);
    }

    void UARTPort::print(const char* str)
    {
        this->write((const uint8_t*)str, strlen(str));
    }
}