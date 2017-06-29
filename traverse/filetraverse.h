#ifndef FILETRAVERSE_H
#define FILETRAVERSE_H

#include <QQuickItem>
#include "traversedfileinfo.h"

class FileTraverse : public QQuickItem
{
public:
    FileTraverse(QQuickItem *parent = Q_NULLPTR);
    QList<TraversedFileInfo>    traverseRecursively(QString folder , int depth = 0);
};

#endif // FILETRAVERSE_H
