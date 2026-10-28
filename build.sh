#!/bin/bash
set -e

if [ ! -f deps.o ]; then
    g++ -std=c++17 -w -O3 \
        -I third_party/raylib/include \
        -I third_party/imgui \
        -I third_party/ \
        -c deps.cpp \
        -o deps.o
fi

g++ -std=c++17 -Wall -Wextra -Wno-unused-variable -Wno-missing-field-initializers -Wno-sign-compare -g -O0 \
    -isystem third_party/raylib/include \
    -isystem third_party/imgui \
    -isystem third_party/rlImGui \
    main.cpp \
    deps.o \
    -o mosaics-editor \
    third_party/raylib/lib/libraylib.a \
    -lm -lpthread -ldl -lrt -l:libX11.so.6

./mosaics-editor
