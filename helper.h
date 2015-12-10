#ifndef HELPER_H
#define HELPER_H

#include <QString>

class Helper
{
public:
    static QString getLessonsDirectory();
    static QString getLessonPath(QString lessonName);
    static QString getContentFilePath(QString lessonName);
    static void createPaths();
};

#endif // HELPER_H
