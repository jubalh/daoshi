#include <QUrl>
#include <QXmlQuery>
#include "checkonline.h"

CheckOnline::CheckOnline(QObject *parent) : QObject(parent),qnam(parent)
{
   connect(&qnam, &QNetworkAccessManager::finished, this, &CheckOnline::httpFinished);
   //connect(reply, &QIODevice::readyRead, this, &HttpWindow::httpReadyRead);
}

bool CheckOnline::updateAvailable()
{
   QUrl url = QUrl::fromUserInput("https://github.com/jubalh/daoshi/releases.atom");
   if (!url.isValid())
   {
      qDebug() << "updateAvailable: URL not valid";
      return false;
   }

   qDebug() << "Filename is " << url.fileName();

   qnam.get(QNetworkRequest(url));

   return true;
}

void CheckOnline::httpFinished(QNetworkReply * reply)
{
   QXmlQuery query;
   QString content = QString(reply->readAll());
   query.setFocus(content);

   // get the title of the latest release and only take the version string
   query.setQuery("declare default element namespace 'http://www.w3.org/2005/Atom'; /feed/entry/title/substring-before(text(),':')");

   QString out;
   query.evaluateTo(&out);
   latest_version_online = out.trimmed();

   qDebug() << latest_version_online;

   emit checkedLatestVersion(latest_version_online);
}
