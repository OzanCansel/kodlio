#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "./deploy.sh <Kit Dizin> <version> seklinde calistirilmalidir."
    echo "ornek => './deploy.sh /homearnes/Qt /home/arnes/Qt/5.9.1/gcc_64 v2'"
    exit
fi

SCRIPT=$(readlink -f '$0')
SCRIPRTDIR=$(dirname '$SCRIPT')
echo $SCRIPT
echo $SCRIPTDIR
QTPATH=$1
KITPATH=$2
VERSION=$3

export PATH=$KITPATH/bin:$QTPATH/Tools/QtInstallerFramework/2.0/bin:$PATH

#yetkiler veriliyor
chmod +x deploy

rm -rf temp
mkdir -p temp
cd temp
mkdir -p build
cd build
echo "Dosyalar derleniyor..."
qmake ../../../../src -spec linux-g++
make

echo "Uygulama paketleniyor..."
cd ..
mkdir -p deploy
cd deploy
../../deploy ../build/kodlio -qmldir=../../../../src -appimage
../../deploy ../build/kodlio -qmldir=../../../../src -appimage
mv Application-x86_64.AppImage kodlio 2>/dev/null

echo "Dosyalar kopyalaniyor"
cd ..
mkdir -p installer
cd installer
cp -r ../../installerTemplate/* .
cp -r ../../../../src/extFiles/linux/* packages/ide/data
cp ../deploy/kodlio packages/ide/data/kodlio

echo "Installer uretiliyor..."
binarycreator -c config/config.xml -p packages KodlioKurulum

mkdir -p ../../../../dist/linux/$VERSION
mv KodlioKurulum ../../../../dist/linux/$VERSION/KodlioKurulum

cd ..
cd ..
rm -rf temp

exit