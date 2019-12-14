#include "../Device.hpp"
#include <stdint.h>

namespace iotlib
{
    class MCP9700
    {
    private:
        Device& device;

    public:
        MCP9700(Device& device);
        ~MCP9700();

        int8_t readTemperature();
    };
}