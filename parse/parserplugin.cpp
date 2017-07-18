#include "parserplugin.h"
#include "errorparser.h"
#include "avr/avrerrorparser.h"

void ParserPlugin::attach(){
    ErrorParser::registerQmlType();
    AvrErrorParser::registerQmlType();
}

ParserPlugin::ParserPlugin()
{

}
