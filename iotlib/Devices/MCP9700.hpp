#include "../Adc.hpp"
#include <stdint.h>

namespace iotlib
{
    class MCP9700
    {
    private:
        Adc& adc;

    public:
        MCP9700(Adc& adc);
        ~MCP9700();

        int8_t readTemperature();
    };
}