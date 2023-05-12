
#! /bin/bash

g++ -O3 -std=c++20 -fsanitize=address -o main main.cpp \
  zlasdtest/container/container.cpp 
