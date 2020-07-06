# Version CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(tcp_udp_server)

# Option
set(CMAKE_CXX_STANDARD 17)
# Compiler-specific options
if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
  add_compile_options(
    -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-promo
  )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_compile_options(/W4 /WX)
endif()

# Source files
file(GLOB_RECURSE SOURCES
  source/*.cpp
  include/*.h
)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Create library
add_library(_${PROJECT_NAME} STATIC ${SOURCES})
# Install lib
install(TARGETS _${PROJECT_NAME} DESTINATION ${PROJECT_NAME}/lib)
# Install includes
install(DIRECTORY include DESTINATION ${PROJECT_NAME})

# Link winsock2 for Windows
if(WIN32)
  target_link_libraries(_${PROJECT_NAME} wsock32 ws2_32)
  set(CMAKE_EXE_LINKER_FLAGS " -static -static-libgcc -static-libstdc++")
endif()
