#include "lesson.h"


QString Lesson::name() const
{
    return mName;
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
