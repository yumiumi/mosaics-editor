#!/bin/bash
set -e

mkdir -p build

# Compile deps.cpp
g++ -std=c++17 -w -g -O3 \
    -I third_party/raylib/include \
    -I third_party/imgui \
    -I third_party/ \
    -c deps.cpp \
    -o build/deps.o

# Compile main.cpp
g++ -std=c++17 -Wall -Wextra -Wno-unused-variable -Wno-missing-field-initializers -Wno-sign-compare -g -O0 \
    -isystem third_party/raylib/include \
    -isystem third_party/imgui \
    -isystem third_party/rlImGui \
    -c main.cpp \
    -o build/main.o

# Link
g++ build/main.o build/deps.o \
    -o build/mosaics-editor \
    third_party/raylib/lib/libraylib.a \
    -lm -lpthread -ldl -lrt -l:libX11.so.6

# Run
./build/mosaics-editor
