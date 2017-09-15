#ifndef STRINGLISTUTIL_H
#define STRINGLISTUTIL_H

#include <QStringList>

class StringListUtil
{
public:

    static void append(QStringList   &list , QStringList &items);
    static void merge(QStringList &first , QStringList &second);
    StringListUtil();
};

#endif // STRINGLISTUTIL_H
