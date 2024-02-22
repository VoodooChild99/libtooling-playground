#!/bin/bash

rm -rf build
mkdir build
cd build || (echo "cd build failed" && exit)

if [ -z "${LLVM_CONFIG}" ];
then
	export LLVM_CONFIG=llvm-config
fi

if [ -z "${CMAKE_BUILD_TYPE}" ];
then
  export CMAKE_BUILD_TYPE=RelWithDebInfo
fi

cmake	..