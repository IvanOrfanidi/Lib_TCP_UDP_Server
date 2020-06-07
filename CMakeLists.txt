# Version CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(tcp_udp_server)

# Option
set(CMAKE_CXX_STANDARD 17)

# Source files
file(GLOB_RECURSE SOURCES 
  src/*.cpp
  include/*.h)

# Create library
add_library(_${PROJECT_NAME} STATIC ${SOURCES})
# Install lib
install(TARGETS _${PROJECT_NAME} DESTINATION ${PROJECT_NAME}/lib)
# Install includes
install(DIRECTORY include DESTINATION ${PROJECT_NAME})
