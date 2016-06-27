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
    QString mVersion;
    QList<Word> mWordList;
public:
    Lesson();
    Lesson(QString name);
    const QList<Word>& wordList() const;
    void setWordList(const QList<Word> &wordList);
    void appendWordList(const Word &word) { mWordList.append(word); }
    void setName(const QString name);
    QString name() const;
    QString error() const;
    void setError(const QString &error);
    QString version() const;
    void setVersion(const QString &version);
};

#endif // LESSON_H
