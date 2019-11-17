#pragma once

namespace iotlib
{
    class Library
    {
    public:
        Library();
        ~Library();

        static void initialize();
        static void finalize();
    };
}