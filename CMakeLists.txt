# Version CMake
cmake_minimum_required(VERSION 3.3)

# Project name
project(tcp_udp_server CXX)

# Option
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -c")

# Source files
file(GLOB_RECURSE SOURCES
  src/*.cpp
  src/*.h)

# Compiling target
add_executable(${PROJECT_NAME} ${SOURCES})

# Link winsock2 for Windows
if(WIN32)
  target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif()

# Link lib
add_library(_tcp_udp_server STATIC ${SOURCES})