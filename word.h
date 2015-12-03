#ifndef WORD_H
#define WORD_H
#include <QString>
#include <QStringList>

class Word
{
private:
    QString pictogram;
    QString pinyin;
    QString translation;
    QStringList exampleSentences;
public:
    Word();
};

#endif // WORD_H
