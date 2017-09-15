#include "stringlistutil.h"

StringListUtil::StringListUtil()
{

}

void StringListUtil::append(QStringList &list, QStringList &items){
    foreach (QString item, items) {
        list.append(item);
    }
}

void StringListUtil::merge(QStringList &first, QStringList &second){
    foreach (QString str, second) {
        if(!first.contains(str))
            first.append(str);
    }
}

