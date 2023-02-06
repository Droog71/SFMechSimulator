#! /bin/bash
g++ main.cpp $PWD/src/*.cpp -Iinclude -o SFMechSimulator -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -v
