#include "runoptions.h"
#include <QtQml>

void RunOptions::registerQmlType(){
    qmlRegisterType<RunOptions>("Kodlio" , 1 , 0 , "RunOptions");
}

RunOptions::RunOptions(QQuickItem *parent) : Options(parent){

}
