#!/bin/bash
set -e

# Compile deps.cpp
g++ -std=c++17 -w -g -O3 \
    -I third_party/raylib/include \
    -I third_party/imgui \
    -I third_party/ \
    -c deps.cpp \
    -o deps.o

# Compile main.cpp
g++ -std=c++17 -Wall -Wextra -Wno-unused-variable -Wno-missing-field-initializers -Wno-sign-compare -g -O0 \
    -isystem third_party/raylib/include \
    -isystem third_party/imgui \
    -isystem third_party/rlImGui \
    -c main.cpp \
    -o main.o

# Link
g++ main.o deps.o \
    -o mosaics-editor \
    third_party/raylib/lib/libraylib.a \
    -lm -lpthread -ldl -lrt -l:libX11.so.6

# Run
./mosaics-editor
