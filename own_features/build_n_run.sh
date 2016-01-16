#!/bin/bash

clear
cd build/
cmake ..
make
cd ../bin
./own_features ~/Scaricati/fontana_trevi.jpg
