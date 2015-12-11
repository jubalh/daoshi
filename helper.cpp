#include "helper.h"
#include <QStandardPaths>
#include <QDir>

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

void Helper::createPaths()
{
    QDir dir(getLessonsDirectory());
    if(!dir.exists())
    {
        dir.mkpath(getLessonsDirectory());
    }
}

QString Helper::stringListToHtml(const QStringList &list)
{
   QString sHtml;

   if(list.count() > 1)
   {
       sHtml = "<ul>";
       for(int i=0; i < list.count(); i++)
       {
           sHtml = sHtml + "<li>" + list.at(i) + "</li>";
       }
       sHtml += "</ul>";
   }
   else
       sHtml = list.join("");

   return sHtml;
}
