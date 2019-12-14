#include "Library.blank.hpp"

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
        #warning Not implemented!
    }

    void Library::finalize()
    {
        #warning Not implemented!
    }
}