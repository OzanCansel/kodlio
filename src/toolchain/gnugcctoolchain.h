#ifndef GNUGCCTOOLCHAIN_H
#define GNUGCCTOOLCHAIN_H

#include <QQuickItem>
#include <QString>

class GnuGccToolchain : public  QQuickItem
{

    Q_OBJECT

public:

    GnuGccToolchain(QQuickItem *parent = Q_NULLPTR);
    void        compileProject(QString path , QString outPath , QStringList extraFolders);

};

#endif // GNUGCCTOOLCHAIN_H
