#include "eventcontext.h"

EventContext::EventContext(QQuickItem *parent) : QQuickItem(parent)
{

}

void EventContext::send(int msg, QVariantList args){
    emit message(msg , args);
}
