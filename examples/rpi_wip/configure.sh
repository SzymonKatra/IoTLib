#!/bin/bash
rm -rf build
mkdir build
mkdir build/Debug
mkdir build/Release
( cd build/Debug && cmake -DCMAKE_BUILD_TYPE=Debug -G"Unix Makefiles" ../../ )
( cd build/Release && cmake -DCMAKE_BUILD_TYPE=Release -G"Unix Makefiles" ../../ )