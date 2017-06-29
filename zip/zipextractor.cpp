#include "zipextractor.h"

ZipExtractor::ZipExtractor(){
    _debugEnabled = false;
}

void ZipExtractor::setDebugEnabled(bool enabled){
    _debugEnabled = enabled;
}

bool ZipExtractor::debugEnabled(){
    return  _debugEnabled;
}
