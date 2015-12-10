#ifndef LESSON_H
#define LESSON_H

#include "word.h"
#include <QString>
#include <QList>

class Lesson
{
private:
    QString mName;
    QList<Word> mWordList;
public:
    Lesson();
    Lesson(QString name);
    QList<Word> wordList() const;
    void setWordList(const QList<Word> &wordList);
    QString name() const;
};

#endif // LESSON_H
