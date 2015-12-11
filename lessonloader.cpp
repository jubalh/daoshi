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
    Lesson result;

    qDebug() << "lesson name:" << this->mLessonName;
    bool bValidLesson = this->checkLessonStructure();

    if (bValidLesson)
    {
        result = this->loadLesson();
        result.setName(this->mLessonName);
    }
    else
    {
       QString msg = "Structure of lesson is not valid";
       qDebug() << msg;
       result.setError(msg);
    }

    emit loaded(result);
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

Lesson LessonLoader::loadLesson()
{
    QDomDocument document;
    Lesson retLesson;
    QString msg;

    QFile lessonFile(Helper::getContentFilePath(this->mLessonName));
    if (!lessonFile.open(QIODevice::ReadOnly))
    {
        msg = "Failed to open " + lessonFile.fileName();
        qDebug() << msg;
    }

    if (!document.setContent(&lessonFile))
    {
        msg = "Failed to load DOM " + lessonFile.fileName();
        qDebug() << msg;
    }
    lessonFile.close();
    retLesson.setError(msg);

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

        QDomNodeList audios = wordElement.elementsByTagName("audio");
        if (audios.count() >= 1)
        {
            w.setAudio(audios.at(0).toElement().text());
        }

        wordList.append(w);
    }

    retLesson.setWordList(wordList);

    QDomNodeList versionNL = root.elementsByTagName("version");
    retLesson.setVersion(versionNL.at(0).toElement().text());

    return retLesson;
}
