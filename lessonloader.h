#ifndef LESSONLOADER_H
#define LESSONLOADER_H

#include "word.h"
#include "lesson.h"
#include <QThread>
#include <QDomDocument>

class LessonLoader
{
private:
    bool checkLessonStructure(QString name) const;
    QStringList parseXmlIntoStringList(QDomNodeList xmlList, QString singleTagName);
public:
    Lesson loadLesson(QString name) const;
};

#endif // LESSONLOADER_H
