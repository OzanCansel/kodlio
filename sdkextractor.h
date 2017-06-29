#ifndef SDKEXTRCACTOR_H
#define SDKEXTRCACTOR_H

#include <QObject>

class SdkExtractor : public QObject
{

    Q_OBJECT

public:

    static QString      avrBinPath();
    static QString      arduinoCorePath();
    static QString      variantsStandardPath();
    static QString      avrdudeConfPath();

    SdkExtractor(QObject *parent = Q_NULLPTR);

    bool    checkSdk();
    bool    extractSdk();
    bool    removeSdk();

private:

    static QString     _sdkPath;

};

#endif // SDKEXTRCACTOR_H
