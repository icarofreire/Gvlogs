#!/bin/bash
clear
g++ -std=c++11 main.cpp -o helloworld `pkg-config gtkmm-3.0 --cflags --libs`
