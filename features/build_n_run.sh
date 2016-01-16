#!/bin/bash

clear
cd build/
cmake ..
make
cd ../bin
./features ~/Scaricati/fontana_trevi.jpg
