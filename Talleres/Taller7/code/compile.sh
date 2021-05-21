#!/usr/bin/env bash

source ~/dev/poky/3.1.6/environment-setup-cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi

cmake -G "Unix Makefiles" -DCMAKE_VERBOSE_MAKEFILE=ON -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build build --target all -j

$CC -o sayhello hello.c
