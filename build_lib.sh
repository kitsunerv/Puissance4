#!/bin/bash

if [ ! -f 3rdParty/SDL2/Library/lib/libSDL2.so ]
then 
    cd 3rdParty/SDL2
    ./configure --prefix=$PWD/Library
    make -j install
fi