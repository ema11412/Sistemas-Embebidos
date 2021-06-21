# house-light-control

use RPi + Yocto in an Embedded Systems Introduction Course to provide a PoC of a home automation system

## dependencies

yocto (dunfell, poky 3.1.6)
OpenCV (using version 4.5.2)
cmake 3.16.3

## back-end

MUST source the yocto generated toolchain environment setting script

e.g. (but it could be different)

```
source ~/dev/poky/3.1.6/environment-setup-cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi
```

then we can use cmake to build everything

i.e.

```
cmake -G "Unix Makefiles" -B rpi2-build/release \
  -DOpenCV_DIR=$HOME/dev/pi/opencv/lib/cmake/opencv4 \
  -DBUILD_SHARED_LIBS=OFF -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_BUILD_TYPE=Release \
  -S . # for a debug build
```

we then copy the executable and the shared object file into the SD card

program to server through port 5001 data about the GPIO (alpha status)

## include

for the dynamic/shared library in C, and the snap wrapper for OpenCV

## lib

functionality of the GPIO C library

## test

contains two methods of using functions from a .so file

### ffi

is using it directly from python

```
make ffi # run to test
```

### ipc

is using it through a socket on port 5001

```
make ipc # run to test
```
