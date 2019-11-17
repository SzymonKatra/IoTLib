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
        //options.c_cflag = 0;
        printf("%08X", options.c_cflag);
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

    tcflag_t UARTPort::convertParity(UARTPort::Parity parity)
    {
        switch (parity)
        {
        case UARTPort::Parity::None: return 0;
        case UARTPort::Parity::Even: return PARENB;
        case UARTPort::Parity::Odd: return PARENB | PARODD;
        default: return 0;
        }
    }

    tcflag_t UARTPort::convertStopBits(UARTPort::StopBits stopBits)
    {
        switch (stopBits)
        {
        case UARTPort::StopBits::One: return 0;
        case UARTPort::StopBits::Two: return CSTOPB;
        default: return 0;
        }
    }
}