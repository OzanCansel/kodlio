#include "linenumber.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "parse/parsehelper.h"

void LineNumber::registerQmlType(){
    qmlRegisterType<LineNumber>("Kodlio" , 1 , 0 , "LineNumber");
}

LineNumber::LineNumber(QQuickItem *parent) : QQuickItem(parent)
{
    _lineStart = -1;
    _lineEnd = -1;
    _doc = Q_NULLPTR;
}

//Getters
int LineNumber::lineStart(){
    return _lineStart;
}

int LineNumber::lineEnd(){
    return _lineEnd;
}

QQuickTextDocument* LineNumber::textDocument(){
    return _doc;
}

//Setters
void LineNumber::setLineStart(int val){
    _lineStart = val;
    emit lineStartChanged();
}
void LineNumber::setLineEnd(int val){
    _lineEnd = val;
    emit lineEndChanged();
}

void LineNumber::setTextDocument(QQuickTextDocument *document){
    _doc = document;
     emit textDocumentChanged();
}

int LineNumber::matchIdx(int lineNumber){
    if(lineNumber == 1)
        return 0;

    QString     text = _doc->textDocument()->toPlainText();
    QRegularExpression  lineBreakExpression("[\\n]");
    QRegularExpressionMatchIterator it = lineBreakExpression.globalMatch(text);

    int currIdx = 0;

    lineNumber -= 2;
    while(it.hasNext() && currIdx < lineNumber){
        it.next();
        currIdx++;
    }

    if(it.hasNext()){
        QRegularExpressionMatch match = it.next();

        int pos = match.capturedEnd(0);
        return pos;
    }

    return -1;
}

int LineNumber::matchIdxToLineNumber(int pos){
    if(_doc == Q_NULLPTR)
        return 0;
    QString text = _doc->textDocument()->toPlainText();

    return ParseHelper::calculateLineNumber(text , pos);
}
