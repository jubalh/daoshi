#ifndef HELPER_H
#define HELPER_H

#include <QString>
#include <QStringList>

class Helper
{
public:
    static QString getLessonsDirectory();
    static QString getLessonPath(QString lessonName);
    static QString getContentFilePath(QString lessonName);
    static void createPaths();
    static QString stringListToHtml(const QStringList &list);
};

#endif // HELPER_H
