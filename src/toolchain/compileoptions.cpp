#include "compileoptions.h"

void CompileOptions::registerQmlType(){
    qmlRegisterType<CompileOptions>("Kodlio" , 1 , 0 , "CompileOptions");
}

CompileOptions::CompileOptions(QQuickItem *parent) : Options(parent){

}
