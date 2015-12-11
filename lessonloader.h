#ifndef LESSONLOADER_H
#define LESSONLOADER_H

#include "word.h"
#include "lesson.h"
#include <QThread>
#include <QDomDocument>

class LessonLoader : public QThread
{
    Q_OBJECT
private:
    bool checkLessonStructure();
    QString mLessonName;
    QStringList parseXmlIntoStringList(QDomNodeList xmlList, QString singleTagName);
public:
    explicit LessonLoader(QObject *parent = 0);
    void run();
    void setLessonName(QString name);
    Lesson loadLesson();

signals:
    bool loaded(Lesson lesson);

public slots:

};

#endif // LESSONLOADER_H
