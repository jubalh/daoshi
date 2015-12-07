#ifndef HELPER_H
#define HELPER_H

#include <QString>

class Helper
{
public:
    static QString getLessonsPath();
    static QString getContentFilePath(QString lessonName);
};

#endif // HELPER_H
