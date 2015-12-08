#ifndef LESSONLOADER_H
#define LESSONLOADER_H

#include "word.h"
#include <QThread>

class LessonLoader : public QThread
{
    Q_OBJECT
private:
    bool checkLessonStructure();
    QString mLessonName;
public:
    explicit LessonLoader(QObject *parent = 0);
    void run();
    void setLessonName(QString name);
    QPair<QList<Word>, QString> loadLesson();

signals:
    bool loaded(QList<Word> wordList);

public slots:

};

#endif // LESSONLOADER_H
