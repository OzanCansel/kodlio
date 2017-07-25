#include "kodlioasistant.h"
#include "functionparser.h"
#include "generate/codedescriptiongenerator.h"
#include "generate/func/digitalwritedescgenerator.h"
#include "generate/func/delaydescgenerator.h"
#include "generate/func/serialprintdescgenerator.h"
#include "generate/func/pinmodedescgenerator.h"
#include "generate/func/serialbegindescgenerator.h"
#include "generate/func/digitalreaddescgenerator.h"
#include "generate/func/analogreaddescgenerator.h"
#include "generate/func/tonedescgeneratoro1.h"
#include "generate/func/tonedescgeneratoro2.h"
#include "generate/func/notonedescgenerator.h"
#include "generate/func/pulseindescgeneratoro1.h"
#include "generate/func/pulseindescgeneratoro2.h"
#include "parse/parsehelper.h"
#include <QRegularExpression>

void KodlioAsistant::registerQmlType(){
    qmlRegisterType<KodlioAsistant>("Kodlio" , 1 , 0 , "KodlioAsistant");
}

KodlioAsistant::KodlioAsistant(QQuickItem *parent) : QQuickItem(parent)
{
    _generators << new  DigitalWriteDescGenerator() << new DelayDescGenerator() << new SerialPrintDescGenerator() << new PinModeDescGenerator() << new SerialBeginDescGenerator() << new DigitalReadDescGenerator()
                << new AnalogReadDescGenerator() << new ToneDescGeneratorO1() << new ToneDescGeneratorO2() << new NoToneDescGenerator()
                << new PulseInDescGeneratorO1() << new PulseInDescGeneratorO2();

    setCooldown(2000);
    connect(&_parseCooldown , SIGNAL(timeout()) ,this , SLOT(parseRequired()));
}


//Setters
void KodlioAsistant::setTextDocument(QQuickTextDocument *document){
    _doc = document;
    QTextDocument*  doc = _doc->textDocument();

    modified(true);
    connect(doc , SIGNAL(modificationChanged(bool)) , this , SLOT(modified(bool)));

    emit textDocumentChanged();
}

void KodlioAsistant::setCooldown(int val){
    _parseCooldown.setInterval(val);

    emit cooldownChanged();
}

//Getters
QQuickTextDocument*  KodlioAsistant::textDocument(){
    return _doc;
}

int KodlioAsistant::cooldown(){
    return _parseCooldown.interval();
}

//Slots
void KodlioAsistant::modified(bool modified){
    if(modified && isEnabled()){
        if(_parseCooldown.isActive())
            _parseCooldown.stop();

        _parseCooldown.start();
    }
}

void KodlioAsistant::parseRequired(){
    //Parse basladi
    emit parseStarted();

    QString content = _doc->textDocument()->toPlainText();
    FunctionParser  parser;
    QList<FunctionUsageParsed>  funcs = parser.extractFunctions(content);

    foreach (FunctionUsageParsed fParsed, funcs) {
        foreach (FuncDescGenerator *generator, _generators) {

            QRegularExpression  expr(generator->name());
            //Eğer ki fonksiyona karşılık gelen generator mevcutsa
            if(expr.match(fParsed.functionName()).hasMatch() && generator->argsCount() == fParsed.args().count()){
                QVariantMap map;
                QString desc;
                generator->generate(fParsed , desc);
                int lineNumber = ParseHelper::calculateLineNumber(content , fParsed.matchIdx());
                map["description"]  =   desc;
                map["lineNumber"]   =   lineNumber;
                map["idx"]          =   fParsed.matchIdx();

                emit newComment(map);
            }
        }
    }

    //Parse bitti
    emit parseEnd();
}
