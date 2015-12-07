#include "lessonloader.h"
#include "helper.h"
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QByteArray>
#include <QXmlSchemaValidator>
#include <QXmlSchema>

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
    qDebug() << "lesson name:" << this->mLessonName;
    bool bValidLesson = this->checkLessonStructure();
    if (!bValidLesson)
        qDebug() << "Lesson is not valid";

    //TODO: tell 'loaded' about status
    emit loaded();
}

bool LessonLoader::checkLessonStructure()
{
    QString lessonPath = Helper::getLessonsPath() + "/" + this->mLessonName;

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
    QXmlSchema schema;
    schema.load(schemaStream);
    if(schema.isValid())
        qDebug() << "XML schema is valid";
    else
    {
        qDebug() << "XML schema is invalid";
        return false;
    }
    QXmlSchemaValidator validator(schema);
    if(validator.validate(lesson.readAll()))
        qDebug() << "content.xml is valid";
    else
    {
        qDebug() << "content.xml invalid";
        return false;
    }

    return true;
}
