#!/bin/bash

cmake CMakeLists.txt
make clean
make
rm ./test_data/result.txt

./calculator < ./test_data/test_cases.txt &> ./test_data/result.txt

paste -d"\n" ./test_data/test_cases.txt ./test_data/expected.txt ./test_data/result.txt ./test_data/spaces.txt