#include "word.h"


QString Word::getPictogram() const
{
    return pictogram;
}

void Word::setPictogram(const QString &value)
{
    pictogram = value;
}

QString Word::getPinyin() const
{
    return pinyin;
}

void Word::setPinyin(const QString &value)
{
    pinyin = value;
}

QString Word::getTranslation() const
{
    return translation;
}

void Word::setTranslation(const QString &value)
{
    translation = value;
}

QStringList Word::getExampleSentences() const
{
    return exampleSentences;
}

void Word::setExampleSentences(const QStringList &value)
{
    exampleSentences = value;
}

QString Word::getNote() const
{
    return note;
}

void Word::setNote(const QString &value)
{
    note = value;
}

Word::Word()
{
}

Word::Word(QString pictogram, QString pinyin, QString translation, QString note, QStringList &exampleSentences)
{
    this->pictogram = pictogram;
    this->pinyin = pinyin;
    this->translation = translation;
    this->note = note;
    this->exampleSentences = exampleSentences;
}
