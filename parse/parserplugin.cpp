#include "parserplugin.h"
#include "errorparser.h"
#include "avr/avrerrorparser.h"
#include "kodlioasistant.h"

void ParserPlugin::attach(){
    ErrorParser::registerQmlType();
    AvrErrorParser::registerQmlType();
    KodlioAsistant::registerQmlType();
}

ParserPlugin::ParserPlugin()
{

}
