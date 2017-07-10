#ifndef FILEINFO_H
#define FILEINFO_H

#include <QQuickItem>
#include <QFileInfo>

class FileInfo : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(QString file READ filePath WRITE setFile NOTIFY filePathChanged)

public:

    static void registerQmlType();

    FileInfo(QQuickItem *parent = Q_NULLPTR);
    ~FileInfo();
    FileInfo(QFileInfo &info, QQuickItem *parent = Q_NULLPTR);
    FileInfo(const FileInfo &other);
    FileInfo& operator =(const FileInfo &other);

signals:

    void        filePathChanged();

public slots:

    QString     absolutePath();
    QString     absoluteFilePath();
    QString     baseName();
    QString     bundleName();
    bool        caching();
    QString     canonicalFilePath() const;
    QString     canonicalPath() const;
    QString     completeBaseName() const;
    QString     completeSuffix() const;
    bool        exists();
    QString     fileName() const;
    QString     filePath() const;
    QString     group();
    bool        isAbsolute();
    bool        isBundle();
    bool        isDir();
    bool        isExecutable();
    bool        isFile();
    bool        isHidden();
    bool        isNativePath();
    bool        isReadable();
    bool        isRelative();
    bool        isRoot();
    bool        isSymLink();
    bool        isWritable();
    QString     path();
    qint64      size();
    QString     suffix();
    QString     symLinkTarget();
    void        setFile(QString file);

private:

    QFileInfo   _info;

};

#endif // FILEINFO_H
