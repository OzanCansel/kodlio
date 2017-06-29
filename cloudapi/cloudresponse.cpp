#include "cloudresponse.h"

CloudResponse::CloudResponse()
{

}

CloudResponse::CloudResponse(QJsonObject obj){
    parse(obj);
}

QJsonObject CloudResponse::body(){
    return _body;
}

QString CloudResponse::message(){
    return _message;
}

bool CloudResponse::success(){
    return _success;
}

void CloudResponse::parse(QJsonObject obj , bool bodyIsArray){
    _message = obj["message"].toString();
    _success = obj["success"].toBool();
    _body = obj["body"].toObject();
}
