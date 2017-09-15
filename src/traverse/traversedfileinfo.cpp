#include "traversedfileinfo.h"

TraversedFileInfo::TraversedFileInfo(QFileInfo info,  int depth)
{
    _depth  =   depth;
    _info   =   info;
}

TraversedFileInfo::TraversedFileInfo(const TraversedFileInfo &other){
    _depth      =   other.depth();
    _info       =   other.info();
}

TraversedFileInfo& TraversedFileInfo::operator =(const TraversedFileInfo &other){
    _depth      =   other.depth();
    _info       =   other.info();
}

int         TraversedFileInfo::depth() const{
    return _depth;
}

QFileInfo   TraversedFileInfo::info() const{
    return _info;
}
