#!/bin/bash

rm -fr bin/
mkdir bin
g++ -c source/*.cpp
mv *.o bin/
g++ bin/*.o -o bin/f3rkanoid -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

