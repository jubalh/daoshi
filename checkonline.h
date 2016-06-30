#ifndef CHECKONLINE_H
#define CHECKONLINE_H

#include <QNetworkAccessManager>
#include <QNetworkReply>

class CheckOnline : public QObject
{
   Q_OBJECT
public:
   CheckOnline(QObject *parent);
   bool updateAvailable();
   QStringList getLessonsList();
signals:
    void checkedLatestVersion(QString version);
private slots:
   void httpFinished(QNetworkReply * reply);
private:
   QNetworkAccessManager qnam;
   QString latest_version_online;
};

#endif // CHECKONLINE_H
