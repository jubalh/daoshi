#ifndef ONLINELESSON_H
#define ONLINELESSON_H

#include <QString>

class OnlineLesson
{
private:
   int mId;
   int mVersion;
   QString mName;
   QString mLanguage;
   QString mURL;
   QString mArchive;
   QString mDescription;
public:
   OnlineLesson();
   OnlineLesson(QString name, int id, QString lang, QString url, QString archive, QString desc, int version);
   int getId() const;
   void setId(int value);
   QString getName() const;
   void setName(const QString &name);
   QString getLanguage() const;
   void setLanguage(const QString &language);
   QString getURL() const;
   void setURL(const QString &uRL);
   QString getArchive() const;
   void setArchive(const QString &archive);
   int getVersion() const;
   void setVersion(int version);
   QString getDescription() const;
   void setDescription(const QString &description);
};

#endif // ONLINELESSON_H
