#ifndef LESSON_H
#define LESSON_H

#include "word.h"
#include <QString>
#include <QList>

class Lesson
{
private:
    QString mName;
    QString mError;
    QList<Word> mWordList;
public:
    Lesson();
    Lesson(QString name);
    QList<Word> wordList() const;
    void setWordList(const QList<Word> &wordList);
    void setName(const QString name);
    QString name() const;
    QString error() const;
    void setError(const QString &error);
};

#endif // LESSON_H
