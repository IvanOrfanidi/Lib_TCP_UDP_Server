#!/bin/bash

BUILD_PATH="build"
INSTALL_PATH=${BUILD_PATH}

if [ -n "$1" ]
    then
        INSTALL_PATH=$1
fi

# Delete build path
rm -r ${BUILD_PATH}

mkdir -p ${BUILD_PATH}
cd ${BUILD_PATH}

cmake -G "Unix Makefiles" .. -DCMAKE_INSTALL_PREFIX=../${INSTALL_PATH}
cmake --build .
make install
