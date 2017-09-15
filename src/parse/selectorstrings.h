#ifndef SELECTORSTRINGS_H
#define SELECTORSTRINGS_H

#include <QString>

class SelectorStrings
{
public:

    SelectorStrings();

    QString doubleSelector();
    QString variableNameSelector();
    QString skipWhiteSpace();

private:

    QString _doubleSelector;
    QString _variableNameSelector;
    QString _skipWhiteSpace;

    QString     group(QString str);
};

#endif // SELECTORSTRINGS_H
