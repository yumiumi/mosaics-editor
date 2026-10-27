#!/bin/bash
set -e

g++ -std=c++17 -Wall -Wextra -g -O0 -isystem raylib/include main.cpp -o mosaics-editor raylib/lib/libraylib.a -lm -lpthread -ldl -lrt -l:libX11.so.6

./mosaics-editor
