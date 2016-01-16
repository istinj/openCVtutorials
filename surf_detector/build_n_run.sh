#!/bin/bash

clear
cd build/
cmake ..
make
cd ../bin
./surfDetector ~/Scaricati/IMG_0034.JPG ~/Scaricati/IMG_0036.JPG
