#include "onlinelesson.h"

int OnlineLesson::getVersion() const
{
   return mVersion;
}

void OnlineLesson::setVersion(int version)
{
   mVersion = version;
}

QString OnlineLesson::getDescription() const
{
   return mDescription;
}

void OnlineLesson::setDescription(const QString &description)
{
   mDescription = description;
}

OnlineLesson::OnlineLesson(QString name, int id, QString lang, QString url, QString archive, QString desc, int version)
{
   mName = name;
   mId = id;
   mLanguage = lang;
   mURL = url;
   mArchive = archive;
   mDescription = desc;
   mVersion = version;
}

int OnlineLesson::getId() const
{
   return mId;
}

void OnlineLesson::setId(int value)
{
   mId = value;
}

QString OnlineLesson::getName() const
{
   return mName;
}

void OnlineLesson::setName(const QString &name)
{
   mName = name;
}

QString OnlineLesson::getLanguage() const
{
   return mLanguage;
}

void OnlineLesson::setLanguage(const QString &language)
{
   mLanguage = language;
}

QString OnlineLesson::getURL() const
{
   return mURL;
}

void OnlineLesson::setURL(const QString &uRL)
{
   mURL = uRL;
}

QString OnlineLesson::getArchive() const
{
   return mArchive;
}

void OnlineLesson::setArchive(const QString &archive)
{
   mArchive = archive;
}
