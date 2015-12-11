#include "lessonloader.h"
#include "helper.h"
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QByteArray>
#include <QXmlSchemaValidator>
#include <QXmlSchema>
#include <QDomDocument>

LessonLoader::LessonLoader(QObject *parent) :
    QThread(parent)
{
}

void LessonLoader::setLessonName(QString name)
{
    this->mLessonName = name;
}

void LessonLoader::run()
{
    Lesson l;

    qDebug() << "lesson name:" << this->mLessonName;
    bool bValidLesson = this->checkLessonStructure();

    if (bValidLesson)
    {
        QPair<QList<Word>, QString> result = this->loadLesson();
        QList<Word> wordList = result.first;

        if(result.second.isEmpty())
        {
            l.setName(this->mLessonName);
            l.setWordList(wordList);
        }
        else
        {
            l.setError(result.second);
        }
    }
    else
    {
       QString msg = "Structure of lesson is not valid";
       qDebug() << msg;
       l.setError(msg);
    }

    emit loaded(l);
}

bool LessonLoader::checkLessonStructure()
{
    QString lessonPath = Helper::getLessonsDirectory() + "/" + this->mLessonName;

    //check lesson path
    QDir lessonDir(lessonPath);
    if(!lessonDir.exists())
        return false;

    //check for content file
    QFile lesson(Helper::getContentFilePath(this->mLessonName));
    if(!lesson.exists())
        return false;
    lesson.open(QIODevice::ReadOnly);

    //check for valid xml
    QFile schemaFile(":/schemas/resources/content.xsd");
    schemaFile.open(QIODevice::ReadOnly);
    QByteArray schemaStream = schemaFile.readAll();
    schemaFile.close();
    QXmlSchema schema;
    schema.load(schemaStream);
    if(schema.isValid())
        qDebug() << "XML schema is valid";
    else
    {
        qDebug() << "XML schema is invalid";
        lesson.close();
        return false;
    }
    QXmlSchemaValidator validator(schema);
    QByteArray ba = lesson.readAll();
    lesson.close();
    if(validator.validate(ba))
        qDebug() << "content.xml is valid";
    else
    {
        qDebug() << "content.xml invalid";
        return false;
    }

    return true;
}

QPair<QList<Word>, QString>  LessonLoader::loadLesson()
{
    QDomDocument document;
    QPair<QList<Word>, QString> ret;

    QFile lesson(Helper::getContentFilePath(this->mLessonName));
    if (!lesson.open(QIODevice::ReadOnly))
    {
        QString msg = "Failed to open " + lesson.fileName();
        qDebug() << msg;
        ret.second = msg;
    }

    if (!document.setContent(&lesson))
    {
        QString msg = "Failed to load DOM " + lesson.fileName();
        qDebug() << msg;
        ret.second = msg;
    }
    lesson.close();

    QDomElement root = document.firstChildElement();
    QDomNodeList words = root.elementsByTagName("word");

    qDebug() << "Total: " << words.count();

    QList<Word> wordList;

    for(int i=0; i < words.count(); i++)
    {
        QDomNode wordNode = words.at(i);

        QDomElement wordElement = wordNode.toElement();

        QString picto = wordElement.elementsByTagName("pictogram").at(0).toElement().text();
        QString pin = wordElement.elementsByTagName("pinyin").at(0).toElement().text();
        QString trans = wordElement.elementsByTagName("translation").at(0).toElement().text();
        QString note = wordElement.elementsByTagName("note").at(0).toElement().text();

        QStringList sentenceList;
        QDomNodeList sentences = wordElement.elementsByTagName("sentences").at(0).toElement().elementsByTagName("sentence");
        if(sentences.count() >= 1)
        {
            for(int n=0; n < sentences.count(); n++)
            {
                sentenceList.append(sentences.at(n).toElement().text());
            }
        }

        Word w(picto, pin, trans, note, sentenceList);
        wordList.append(w);
    }

    ret.first = wordList;

    return ret;
}
