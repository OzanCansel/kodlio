#!/bin/bash
KITPATH=$1

#deploy klasoru olusturuluyor
mkdir -p deploy
cd deploy

mkdir -p build
cd build

#build klasorunun icindeyiz
$KITPATH/bin/qmake ../../kodlio.pro -spec linux-g++
make qmake_all

#build klasorunden cikiliyor
cd ..
mkdir -p deploy
cp build/kodlio deploy/kodlio

#Toollar kopyalaniyor

exit