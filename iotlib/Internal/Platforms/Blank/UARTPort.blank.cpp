#include "UARTPort.blank.hpp"
#include <string.h>

namespace iotlib
{
    UARTPort::UARTPort(UARTPortDefinition port, uint32_t baudRate, UARTPort::Parity parity, UARTPort::StopBits stopBits)
    {
        #warning Not implemented!
    }
    UARTPort::~UARTPort()
    {
        #warning Not implemented!
    }

    size_t UARTPort::write(const uint8_t* buffer, size_t size)
    {
        #warning Not implemented!
    }

    size_t UARTPort::read(uint8_t* buffer, size_t size)
    {
        #warning Not implemented!
    }

    void UARTPort::print(const char* str)
    {
        #warning Not implemented!
    }
}