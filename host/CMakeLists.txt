# setup project
cmake_minimum_required(VERSION 3.9)
project(memflow-cmake-example VERSION 1.0 DESCRIPTION "memflow-cmake-example")

# Assuming memflow is located under host/memflow
set(MEMFLOW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/memflow/memflow-ffi")
set(MEMFLOW_LIBRARY_DEBUG "${CMAKE_SOURCE_DIR}/memflow/target/debug/libmemflow_ffi.a")
set(MEMFLOW_LIBRARY_RELEASE "${CMAKE_SOURCE_DIR}/memflow/target/release/libmemflow_ffi.a")

# Debug messages to verify paths
message(STATUS "MEMFLOW_INCLUDE_DIR: ${MEMFLOW_INCLUDE_DIR}")
message(STATUS "MEMFLOW_LIBRARY_DEBUG: ${MEMFLOW_LIBRARY_DEBUG}")
message(STATUS "MEMFLOW_LIBRARY_RELEASE: ${MEMFLOW_LIBRARY_RELEASE}")

# Include directories
include_directories(${MEMFLOW_INCLUDE_DIR})

# Add library
add_library(memflow_ffi STATIC IMPORTED)
set_target_properties(memflow_ffi PROPERTIES
    IMPORTED_LOCATION_DEBUG ${MEMFLOW_LIBRARY_DEBUG}
    IMPORTED_LOCATION_RELEASE ${MEMFLOW_LIBRARY_RELEASE}
)

find_package(Threads)

# Create binary from /src
file(GLOB_RECURSE sample-cpp-sources "src/*.cpp")
file(GLOB_RECURSE sample-sources "src/*.c")
file(GLOB_RECURSE sample-headers "src/*.h")
file(GLOB_RECURSE sample-headers "src/*.hpp")

set(CMAKE_CXX_STANDARD 17)

add_executable(
    example
    ${sample-sources}
    ${sample-cpp-sources}
    ${sample-headers}
)

target_link_libraries(
    example
    debug ${MEMFLOW_LIBRARY_DEBUG}
    optimized ${MEMFLOW_LIBRARY_RELEASE}
    ${CMAKE_THREAD_LIBS_INIT}
    ${CMAKE_DL_LIBS}
    m
)

target_include_directories(
    example PUBLIC
    ${MEMFLOW_INCLUDE_DIR}
)