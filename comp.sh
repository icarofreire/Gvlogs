#!/bin/bash
clear
g++ -std=c++11 main.cpp -o Gvlogs `pkg-config gtkmm-3.0 --cflags --libs`
