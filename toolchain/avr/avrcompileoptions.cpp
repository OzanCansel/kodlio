#include "avrcompileoptions.h"
#include <QtQml>

void AvrCompileOptions::registerQmlType(){
    qmlRegisterType<AvrCompileOptions>("Kodlio" , 1 , 0 , "AvrCompileOptions");
}

AvrCompileOptions::AvrCompileOptions(QQuickItem *parent) : CompileOptions(parent)
{

}
