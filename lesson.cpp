#include "lesson.h"


QString Lesson::name() const
{
    return mName;
}

QString Lesson::error() const
{
    return mError;
}

void Lesson::setError(const QString &error)
{
    mError = error;
}

QString Lesson::version() const
{
    return mVersion;
}

void Lesson::setVersion(const QString &version)
{
    mVersion = version;
}

Lesson::Lesson()
{
}

Lesson::Lesson(QString name)
{
    this->mName = name;
}

QList<Word> Lesson::wordList() const
{
    return mWordList;
}

void Lesson::setWordList(const QList<Word> &wordList)
{
    mWordList = wordList;
}

void Lesson::setName(const QString name)
{
    mName = name;
}
