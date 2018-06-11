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

QStringList Word::getExampleSentences() const
{
    return exampleSentences;
}

void Word::setExampleSentences(const QStringList &value)
{
    exampleSentences = value;
}

void Word::appendExampleSentence(const QString &value)
{
   this->exampleSentences.append(value);
}

QString Word::getNote() const
{
    return note;
}

void Word::setNote(const QString &value)
{
    note = value;
}


QString Word::getAudio() const
{
    return audio;
}

void Word::setAudio(const QString &value)
{
    audio = value;
}

QStringList Word::getTranslations() const
{
    return translations;
}

void Word::setTranslations(const QStringList &value)
{
    translations = value;
}

void Word::appendTranslation(const QString &value)
{
   this->translations.append(value);
}

Word::Word()
{
}

Word::Word(QString pictogram, QString pinyin, QStringList translations, QString note, QStringList &exampleSentences, QString audio)
{
    this->pictogram = pictogram;
    this->pinyin = pinyin;
    this->translations = translations;
    this->note = note;
    this->exampleSentences = exampleSentences;
    this->audio = audio;
}
