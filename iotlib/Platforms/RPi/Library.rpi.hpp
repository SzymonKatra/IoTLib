#pragma once

namespace iotlib
{
    class Library
    {
    private:
        static bool isInitialized;

    public:
        Library();
        ~Library();

        static void initialize();
        static void finalize();
    };
}