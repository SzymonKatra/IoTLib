#pragma once

#include <stdint.h>
#include <driver/i2c.h>

namespace iotlib
{
    namespace esp8266
    {
        typedef i2c_port_t I2CBusDefinition;
        const I2CBusDefinition I2C_Bus0 = I2C_NUM_0;

        typedef gpio_num_t I2CSdaPinDefinition;
        const I2CSdaPinDefinition I2C_SDA_GPIO4 = GPIO_NUM_4;

        typedef gpio_num_t I2CSclPinDefinition;
        const I2CSdaPinDefinition I2C_SCL_GPIO5 = GPIO_NUM_5;
    }

    typedef esp8266::I2CBusDefinition I2CBusDefinition;
    typedef esp8266::I2CSdaPinDefinition I2CSdaPinDefinition;
    typedef esp8266::I2CSclPinDefinition I2CSclPinDefinition;

    // todo: error handling
    class I2CBus
    {
    public:
        enum class ReadAckMode
        {
            Nack,
            Ack,
            AckButLastNack,
        };

    private:
        I2CBusDefinition bus;
        i2c_cmd_handle_t currentWriteCmd;
        bool currentWriteCheckAck;

    public:
        I2CBus(I2CBusDefinition bus, I2CSdaPinDefinition sdaPin, I2CSclPinDefinition sclPin);
        ~I2CBus();

        void write(uint8_t address, const uint8_t* data, size_t length, bool checkAck = true);
        void read(uint8_t address, uint8_t* data, size_t length, ReadAckMode ackMode, bool checkAddressAck = true);

        void beginWrite(uint8_t address, bool checkAck = true);
        void write(const uint8_t* data, size_t length);
        void endWrite();

    private:
        i2c_ack_type_t convertReadAckMode(ReadAckMode ackMode);
    };
}