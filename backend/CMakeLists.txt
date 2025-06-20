cmake_minimum_required(VERSION 3.10)
project(cpp_backend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add vendor directory for headers
include_directories(vendor)

add_executable(cpp_backend main.cpp)

# Example of how you might find and link a library like Boost for system threads
find_package(Threads REQUIRED)
target_link_libraries(cpp_backend PRIVATE Threads::Threads) 