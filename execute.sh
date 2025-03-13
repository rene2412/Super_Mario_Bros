#!/bin/bash

g++ -o main main.cpp mario.cpp $(pkg-config --libs --cflags raylib)
if [ $? -eq 0 ]; then
    ./main
else
    echo "Compilation failed."
fi

