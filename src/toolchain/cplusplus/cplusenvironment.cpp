#include "cplusenvironment.h"
#include <QCoreApplication>
#include <QDir>

CPlusEnvironment::CPlusEnvironment(QQuickItem *parent) : Environment(parent){
    set("g++" , "g++");
    set("gcc" , "gcc");
}
