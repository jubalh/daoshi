#include "helper.h"
#include <QStandardPaths>

QString Helper::getLessonsDirectory()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) +  "/lessons";
}

QString Helper::getLessonPath(QString lessonName)
{
    return getLessonsDirectory() + "/" + lessonName;
}

QString Helper::getContentFilePath(QString lessonName)
{
    return getLessonPath(lessonName) + "/content.xml";
}
