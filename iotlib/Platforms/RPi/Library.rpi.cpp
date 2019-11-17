#include "Library.rpi.hpp"
#include "bcm2835.h"
#include "../../System.hpp"

namespace iotlib
{
    bool Library::isInitialized = false;

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
        if (Library::isInitialized)
        {
            System::error("IoTLib is already initialized!");
            return;
        }

        bcm2835_init();

        Library::isInitialized = true;
    }

    void Library::finalize()
    {
        bcm2835_close();
    }
}