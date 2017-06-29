#include "highlighter.h"
#include <QTextDocument>
#include <QTextCursor>
#include <QDebug>

//! [0]
Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(QColor("#28A828"));
//    keywordFormat.setForeground(QColor("#ff0000"));
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
        //! [0] //! [1]
    }
    //! [1]

    //! [2]
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);
    //! [2]

    //! [3]
    //    singleLineCommentFormat.setForeground(Qt::red);
    singleLineCommentFormat.setForeground(QColor("#ff0000"));
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::red);
    //! [3]

    //! [4]
    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);
    //! [4]

    //! [5]
    //    functionFormat.setFontWeight(QFont::Bold);
        functionFormat.setForeground(QColor("#FFA500"));
//    functionFormat.setForeground(QColor("#00979d"));
    functionFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);
    //! [5]

    //! [6]
    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");

    delayFunctionExpression = QRegExp("delay\\([0-9]+\\);");

    includeFormat.setFontItalic(true);
    includeFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\#include");
    rule.format = includeFormat;
    highlightingRules.append(rule);
}
//! [6]

//! [7]
void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

//    int idx = delayFunctionExpression.indexIn(text);
//    if(idx >= 0){
//        qDebug() << "Delay func. detected";

//        QTextCursor cursor = document()->find(delayFunctionExpression);
//    }

    //! [7] //! [8]
    setCurrentBlockState(0);
    //! [8]

    //! [9]
    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    //! [9] //! [10]
    while (startIndex >= 0) {
        //! [10] //! [11]
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                    + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
//! [11]

void Highlighter::setClassColor(QColor col){
    classFormat.setForeground(col);
}

void Highlighter::setKeywordColor(QColor col){
    keywordFormat.setForeground(col);
}

void Highlighter::setSingleLineColor(QColor col){
    singleLineCommentFormat.setForeground(col);
}

void Highlighter::setMultilineColor(QColor col){
    multiLineCommentFormat.setForeground(col);
}

void Highlighter::setQuatationColor(QColor col){
    quotationFormat.setForeground(col);
}

void Highlighter::setFunctionColor(QColor col){
    functionFormat.setForeground(col);
}

void Highlighter::setIncludeColor(QColor col){
    includeFormat.setForeground(col);
}
