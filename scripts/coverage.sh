#! /bin/sh

set -ex

cmake -H. -B.build

export GTEST_COLOR=1
CMAKE_CONFIG_OPTS="-DCMAKE_BUILD_TYPE=Debug"
CMAKE_OPTS="$CMAKE_CONFIG_OPTS"
cmake -H. -B .build $CMAKE_OPTS
cmake --build .build
cmake --build .build --target test -- ARGS="--verbose"

cmake -H. -B .build -DBUILD_COVERAGE=On
cmake --build .build --target gcov
cmake --build .build --target test
gcovr -r  .