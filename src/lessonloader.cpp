#include "lessonloader.h"
#include "helper.h"
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QByteArray>
#include <QXmlSchemaValidator>
#include <QXmlSchema>
#include <QXmlDefaultHandler>
#include <QXmlSimpleReader>
#include <QXmlInputSource>
#include <QStack>

class LessonXMLHandler : public QXmlDefaultHandler {
public:
   LessonXMLHandler(Lesson &lesson) : QXmlDefaultHandler(), lesson(lesson) {
   }

   virtual ~LessonXMLHandler() {}

   bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts) override {
      current_elements.push(localName);
      qDebug() << "startElement" << localName;
      if (current_elements.top() == "word")
         currentWord = Word();
      current_text.push(QString());
      return true;
   }

   bool characters(const QString &ch) override {
      current_text.top().append(ch);
      return true;
   }

   bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName) override {
      qDebug() << "endElement" << localName;
      if (current_elements.top() != localName)
         return false;

      if (current_elements.top() == "pictogram")
         currentWord.setPictogram(current_text.top());
      else  if (current_elements.top() == "pinyin")
         currentWord.setPinyin(current_text.top());
      else  if (current_elements.top() == "translation")
         currentWord.appendTranslation(current_text.top());
      else  if (current_elements.top() == "sentence")
         currentWord.appendExampleSentence(current_text.top());
      else  if (current_elements.top() == "note")
         currentWord.setNote(current_text.top());
      else  if (current_elements.top() == "audio")
         currentWord.setAudio(current_text.top());
      else if (current_elements.top() == "version")
         lesson.setVersion(current_text.top());
      else  if (current_elements.top() == "word")
         lesson.appendWordList(currentWord);

      current_elements.pop();
      current_text.pop();
      return true;
   }

private:
   Word currentWord;
   Lesson &lesson;
   QStack<QString> current_elements;
   QStack<QString> current_text;
};

bool LessonLoader::checkLessonStructure(QString name) const
{
    QString lessonPath = Helper::getLessonsDirectory() + "/" + name;

    //check lesson path
    QDir lessonDir(lessonPath);
    if(!lessonDir.exists())
        return false;

    //check for content file
    QFile lesson(Helper::getContentFilePath(name));
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

Lesson LessonLoader::loadLesson(QString name) const
{
    Lesson retLesson;

    qDebug() << "lesson name:" << name;
    bool bValidLesson = this->checkLessonStructure(name);

    if (!bValidLesson)
    {
       QString msg = "Structure of lesson is not valid";
       qDebug() << msg;
       retLesson.setError(msg);
       return retLesson;
    }

    retLesson.setName(name);

    QFile lessonFile(Helper::getContentFilePath(name));
    if (!lessonFile.open(QIODevice::ReadOnly))
    {
        "Failed to open " + lessonFile.fileName();
        qDebug() << "Failed to open " << lessonFile.fileName();
    }

    QXmlInputSource *source = new QXmlInputSource(&lessonFile);
    LessonXMLHandler handler(retLesson);
    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);
    if (!reader.parse(source))
       retLesson.setError("Error while parsing");

    qDebug() << retLesson.wordList().length();
    return retLesson;
}

QStringList LessonLoader::parseXmlIntoStringList(QDomNodeList xmlList, QString singleTagName)
{
    QStringList stringList;
    QDomNodeList nodeList = xmlList.at(0).toElement().elementsByTagName(singleTagName);
    if(nodeList.count() >= 1)
    {
        for(int n=0; n<nodeList.count(); n++)
        {
            stringList.append(nodeList.at(n).toElement().text());
        }
    }

    return stringList;
}
