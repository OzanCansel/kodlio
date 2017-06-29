#ifndef CLOUDRESPONSE_H
#define CLOUDRESPONSE_H

#include <QJsonObject>

class CloudResponse
{

public:

    CloudResponse();
    CloudResponse(QJsonObject   obj);

    void        parse(QJsonObject obj , bool bodyIsArray = false);

    QJsonObject body();
    QString     message();
    bool        success();

private:

    QString     _message;
    bool        _success;
    QJsonObject _body;
};

#endif // CLOUDRESPONSE_H
