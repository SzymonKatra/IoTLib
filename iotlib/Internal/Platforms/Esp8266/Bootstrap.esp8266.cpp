#ifdef IOTLIB_BOOTSTRAP

#include "../../../Library.hpp"

int main();

extern "C"
{
    void app_main()
    {
        iotlib::Library::initialize();

        main();

        iotlib::Library::finalize();
    }
}

#endif