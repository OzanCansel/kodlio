#ifndef ZIPEXTRACTOR_H
#define ZIPEXTRACTOR_H

#include <QString>
#include <QObject>

class ZipExtractor : public QObject
{


public:

    ZipExtractor();
    virtual bool    unzip(QString zipFile , QString outputFolder , bool overwrite) = 0;
    void        setDebugEnabled(bool enabled);
    bool        debugEnabled();

private:

    bool    _debugEnabled;

};

#endif // ZIPEXTRACTOR_H
