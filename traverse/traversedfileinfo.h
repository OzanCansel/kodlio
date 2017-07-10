#ifndef TRAVERSEDFILEINFO_H
#define TRAVERSEDFILEINFO_H

#include <QQuickItem>
#include <QFileInfo>

class TraversedFileInfo : public  QQuickItem
{

public:

    TraversedFileInfo( QFileInfo info , int depth );
    TraversedFileInfo &operator =(const TraversedFileInfo &other);
    TraversedFileInfo(const TraversedFileInfo &other);


public slots:

    int         depth() const;
    QFileInfo   info() const;

private:

    int         _depth;
    QFileInfo   _info;

};

#endif // FILEINFO_H
