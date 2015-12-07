#include "helper.h"
#include <QStandardPaths>

QString Helper::getLessonsPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) +  "/lessons";
}

QString Helper::getContentFilePath(QString lessonName)
{
    return getLessonsPath() + "/" + lessonName + "/content.xml";
}
