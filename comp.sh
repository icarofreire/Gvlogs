#!/bin/bash
clear
g++ main.cpp -o helloworld `pkg-config gtkmm-3.0 --cflags --libs`
