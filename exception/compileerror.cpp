#include "compileerror.h"

CompileError::CompileError(QString err){
    this->_err = err;
}

QString CompileError::err(){
    return _err;
}
