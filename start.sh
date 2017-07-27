#!/bin/bash

rm out/*.o

g++ -c -std=c++0x source/*.cpp
mv *.o out/
g++ out/*.o -o out/f3rkanoid -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
#export LD_LIBRARY_PATH=/home/fgimenez/data/sdk/sfml-2.1/lib && ./sfml-app
