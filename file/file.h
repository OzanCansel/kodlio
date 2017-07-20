#ifndef FILE_H
#define FILE_H

#include <QQuickItem>

class File : public QQuickItem
{
    Q_OBJECT

public:

    static void     registerQmlType();
    File(QQuickItem *parent = Q_NULLPTR);

public slots:

    bool        createFile(QString path);
    bool        createGenericTemplatedFile(QString path);
    bool        removeFile(QString path);
    bool        createDir(QString root , QString newFolder);

};

#endif // FILE_H
