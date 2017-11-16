#ifndef CHECKONLINE_H
#define CHECKONLINE_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QXmlQuery>

class CheckOnline : public QObject
{
   Q_OBJECT
public:
   CheckOnline(QObject *parent);
   bool updateAvailable();
   bool getAvailableOnlineLessons();
signals:
    void checkedLatestVersion(QString version);
    void receivedAvailLessonsList(QString text);
private slots:
   void httpFinished(QNetworkReply * reply);
private:
   bool retrieveFromUrl(QString urlString);
   void httpFinished_LatestVersion(QXmlQuery &query);
   void httpFinished_AvailableOnlineLessons(QXmlQuery &query);
   QNetworkAccessManager qnam;
   QString latest_version_online;
};

#endif // CHECKONLINE_H
