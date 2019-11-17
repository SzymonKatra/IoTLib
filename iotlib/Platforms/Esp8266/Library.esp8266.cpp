#include "Library.esp8266.hpp"

namespace iotlib
{
    Library::Library()
    {
        Library::initialize();
    }

    Library::~Library()
    {
        Library::finalize();
    }

    void Library::initialize()
    {
    }

    void Library::finalize()
    {
    }
}