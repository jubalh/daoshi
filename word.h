#ifndef WORD_H
#define WORD_H
#include <QObject>
#include <QString>
#include <QStringList>

class Word
{
private:
    QString pictogram;
    QString pinyin;
    QString translation;
    QStringList exampleSentences;
    QString note;
    QString audio;
public:
    Word();
    Word(QString pictogram,
         QString pinyin,
         QString translation,
         QString note,
         QStringList &exampleSentences);
    QString getPictogram() const;
    void setPictogram(const QString &value);
    QString getPinyin() const;
    void setPinyin(const QString &value);
    QString getTranslation() const;
    void setTranslation(const QString &value);
    QStringList getExampleSentences() const;
    void setExampleSentences(const QStringList &value);
    QString getNote() const;
    void setNote(const QString &value);
    QString getAudio() const;
    void setAudio(const QString &value);
};

#endif // WORD_H
