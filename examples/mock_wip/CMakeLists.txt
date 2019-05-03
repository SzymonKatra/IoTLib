cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(PROJECT_NAME Mock-WIP)
set(OUTPUT_DEBUG Debug/bin)
set(OUTPUT_RELEASE Release/bin)
set(IOTLIB_DIR)
set(IOTLIBPLATFORM_DIR)

project(${PROJECT_NAME})

# Define Release by default.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
  message(STATUS "Build type not specified: Use Release by default.")
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_DEBUG}")
  add_definitions(-DDEBUG_AUTOSTART)
else()
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_REL}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_REL}")
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_REL}")
endif()

set (CMAKE_CXX_STANDARD 11)

if(NOT MSVC)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
   endif()
endif(NOT MSVC)

file(GLOB_RECURSE SRC_FILES
    iotlib/*.h
    iotlib/*.c
    iotlib_mock/*.h
    iotlib_mock/*.c
)

add_executable(${PROJECT_NAME}
        ${SRC_FILES}
        main.c
        )

target_link_libraries(${PROJECT_NAME})
