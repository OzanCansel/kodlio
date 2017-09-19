#!bin/bash

if [ "$#" -ne 3 ]; then
	echo "deploy.sh <Qt Dizin> <Kit Dizin> <version> seklinde calistirilmalidir."
	echo "ornek => " 'sh deploy.sh /c/Qt /c/Qt/5.9.1/mingw53_32 v1'
	exit
fi

SCRIPTDIR=$(pwd)

QTPATH=$1
KITPATH=$2
VERSION=$3
MAKE_COMMAND=mingw32-make.exe
DEPLOY_PATH=$KITPATH\\bin\\windeployqt.exe
SRC_DIR=$(realpath -sm "$SCRIPTDIR/../../src")
TEMP_DIR="$SCRIPTDIR/temp"
INSTALLER_DIR="$SCRIPTDIR/temp/installer"
DEPLOY_DIR="$SCRIPTDIR/temp/deploy"
BUILD_DIR="$SCRIPTDIR/temp/build"
DIST_DIR=$(realpath -sm "$SCRIPTDIR/../../dist")
INSTALLER_DIST_DIR=$(realpath -sm "$SCRIPTDIR/../../dist/windows/$VERSION")

export PATH=$KITPATH/bin:$QTPATH/Tools/QtInstallerFramework/2.0/bin:$QTPATH/Tools/mingw530_32/bin:$PATH

#temp klasoru temizleniyor 
rm -rf temp
#temp klasoru olusturuluyor
mkdir -p "$TEMP_DIR"
mkdir -p "$BUILD_DIR" 
mkdir -p "$DEPLOY_DIR"
mkdir -p "$INSTALLER_DIR"
#temp klasoruna giriliyor	temp
cd "$BUILD_DIR"
echo "Dosyalar derleniyor..."
#qmake kullanilarak makefile uretiliyor
qmake "$SRC_DIR" -spec win32-g++
#Proje derleniyor
$MAKE_COMMAND

echo "Uygulama paketleniyor..."
#deploy klasorune giriliyor
cd "$DEPLOY_DIR"
#Uygulama deploy islemi baslatiliyor
cp "$BUILD_DIR/release/kodlio.exe" "$DEPLOY_DIR/kodlio.exe"
windeployqt.exe "$DEPLOY_DIR\\kodlio.exe" --qmldir="$SRC_DIR" --release


echo "Dosyalar kopyalaniyor..."
cp -r "$SCRIPTDIR/installerTemplate/"* "$INSTALLER_DIR"
cp -r "$SRC_DIR/extFiles/windows/"* "$INSTALLER_DIR/packages/ide/data"
cp -r "$DEPLOY_DIR/"* "$INSTALLER_DIR/packages/ide/data"

echo "Installer uretiliyor"
cd "$INSTALLER_DIR"
binarycreator -c config\\config.xml -p packages KodlioKurulum.exe

mkdir -p "$INSTALLER_DIST_DIR"
#mkdir -p ../../../../dist/linux/$VERSION
mv "$INSTALLER_DIR/KodlioKurulum.exe" "$INSTALLER_DIST_DIR/KodlioKurulum.exe"

echo "Installer => "
echo "$INSTALLER_DIST_DIR/KodlioKurulum.exe"
echo "dizinine kopyalandi."

cd "$SCRIPTDIR"
#derleme dosyasi siliniyor
echo "Gereksiz dosyalar temizleniyor..."
rm -rf "$TEMP_DIR"

echo "Islem basarili!"

read -r "Cikis icin bir tusa basiniz"

#cikis yapiliyor
exit