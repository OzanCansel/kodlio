#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QQuickItem>
#include <QFileSystemModel>
#include "file/fileinfo.h"

class FileTree : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath NOTIFY rootPathChanged)
    Q_PROPERTY(QFileSystemModel* model READ model NOTIFY modelChanged)
    Q_PROPERTY(QModelIndex rootIndex READ rootIndex NOTIFY rootIndexChanged)

public:

    static void         registerQmlType();
    FileTree(QQuickItem *parent = Q_NULLPTR);
    void                setRootPath(QString path);
    QModelIndex         rootIndex();
    QFileSystemModel*   model();
    QString             rootPath();

public slots:

    QString             fileName(QModelIndex idx);

signals:

    void                rootPathChanged();
    void                rootIndexChanged();
    void                modelChanged();

private:

    QFileSystemModel    _model;
    QString             _rootPath;

};

#endif // FILEBROWSER_H
