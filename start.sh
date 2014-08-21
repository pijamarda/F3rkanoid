#!/bin/bash

rm *.o

g++ -c -std=c++0x *.cpp -I /home/zeneke/data/sdk/sfml-2.1/include
g++ *.o -o sfml-app -L /home/zeneke/data/sdk/sfml-2.1/lib -lsfml-graphics -lsfml-window -lsfml-system
#export LD_LIBRARY_PATH=/home/zeneke/data/sdk/sfml-2.1/lib && ./sfml-app
