#include <QUrl>
#include <QXmlResultItems>
#include "checkonline.h"

#define URL_VERSION "https://github.com/jubalh/daoshi/releases.atom"
#define URL_AVAILABLE_LESSONS  "https://raw.githubusercontent.com/jubalh/daoshi-available-lessons/master/available-lessons.xml"

CheckOnline::CheckOnline(QObject *parent) : QObject(parent),qnam(parent)
{
   connect(&qnam, &QNetworkAccessManager::finished, this, &CheckOnline::httpFinished);
}

bool CheckOnline::retrieveFromUrl(QString urlString)
{
   QUrl url = QUrl::fromUserInput(urlString);
   if (!url.isValid())
   {
      qDebug() << "URL not valid " << urlString;
      return false;
   }

   qDebug() << "Filename is " << url.fileName();

   qnam.get(QNetworkRequest(url));
   return true;
}

bool CheckOnline::updateAvailable()
{
   if (!retrieveFromUrl(URL_VERSION))
      return false;

   return true;
}

bool CheckOnline::getAvailableOnlineLessons()
{
   if (!retrieveFromUrl(URL_AVAILABLE_LESSONS))
      return false;

   return true;
}

void CheckOnline::httpFinished(QNetworkReply * reply)
{
   QXmlQuery query;

   QString content = QString(reply->readAll());
   if (content.isEmpty())
   {
      qDebug() << "Error: HTTP reply is empty";
      return;
   }
   query.setFocus(content);

   //qDebug() << content;
   query.setFocus(content);

   if (reply->request().url().toString().compare(URL_VERSION) == 0)
      httpFinished_LatestVersion(query);
   else if (reply->request().url().toString().compare(URL_AVAILABLE_LESSONS) == 0)
      httpFinished_AvailableOnlineLessons(query);
}

void CheckOnline::httpFinished_LatestVersion(QXmlQuery &query)
{
   // get the title of the latest release and only take the version string
   query.setQuery("declare default element namespace 'http://www.w3.org/2005/Atom'; /feed/entry/title/substring-before(text(),':')");

   QString out;
   query.evaluateTo(&out);
   latest_version_online = out.trimmed();

   qDebug() << latest_version_online;

   emit checkedLatestVersion(latest_version_online);
}

void CheckOnline::httpFinished_AvailableOnlineLessons(QXmlQuery &query)
{
   query.setQuery("/lessons/lesson");
   //lessons/lesson[@id=1]
   QString out;
   query.evaluateTo(&out);
   qDebug() << out.trimmed();

   //TODO: emmit signal containing available lessons
}
