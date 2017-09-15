#include "codedescriptiongenerator.h"
#include "func/digitalwritedescgenerator.h"
#include "func/delaydescgenerator.h"
#include "func/serialprintdescgenerator.h"
#include "func/pinmodedescgenerator.h"
#include "func/serialbegindescgenerator.h"
#include "func/digitalreaddescgenerator.h"
#include "func/analogreaddescgenerator.h"
#include "func/tonedescgeneratoro1.h"
#include "func/tonedescgeneratoro2.h"
#include "func/notonedescgenerator.h"
#include "func/pulseindescgeneratoro1.h"
#include "func/pulseindescgeneratoro2.h"
#include "parse/parsehelper.h"
#include <QQmlListProperty>
#include <QVariantMap>
#include <QRegularExpression>

CodeDescriptionGenerator::CodeDescriptionGenerator(QQuickItem *parent) : QQuickItem(parent)
{
    _generators << new  DigitalWriteDescGenerator() << new DelayDescGenerator() << new SerialPrintDescGenerator() << new PinModeDescGenerator() << new SerialBeginDescGenerator() << new DigitalReadDescGenerator()
                << new AnalogReadDescGenerator() << new ToneDescGeneratorO1() << new ToneDescGeneratorO2() << new NoToneDescGenerator()
                << new PulseInDescGeneratorO1() << new PulseInDescGeneratorO2();
}

void CodeDescriptionGenerator::retrieveFunctionDescriptions(QString &text){

    QList<FunctionUsageParsed> parsedFuncs = _parser.extractFunctions(text);

    foreach (FunctionUsageParsed fParsed, parsedFuncs) {
        foreach (FuncDescGenerator *generator, _generators) {

            QRegularExpression  expr(generator->name());
            //Eğer ki fonksiyona karşılık gelen generator mevcutsa
            if(expr.match(fParsed.functionName()).hasMatch() && generator->argsCount() == fParsed.args().count()){
                QVariantHash map;
                QString desc;
                generator->generate(fParsed , desc);
                int lineNumber = ParseHelper::calculateLineNumber(text , fParsed.matchIdx());
                map["description"]  =   desc;
                map["lineNumber"]   =   lineNumber;

                emit descriptionAppend(map);
            }
        }
    }
}
