#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QString>

class FileUtil
{
public:
    FileUtil();
    static QString  readContent(QString &file);
};

#endif // FILEUTIL_H
