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
    QStringList translations;
    QStringList exampleSentences;
    QString note;
    QString audio;
public:
    Word();
    Word(QString pictogram,
         QString pinyin,
         QStringList translations,
         QString note,
         QStringList &exampleSentences);
    QString getPictogram() const;
    void setPictogram(const QString &value);
    QString getPinyin() const;
    void setPinyin(const QString &value);
    QStringList getExampleSentences() const;
    void setExampleSentences(const QStringList &value);
    QString getNote() const;
    void setNote(const QString &value);
    QString getAudio() const;
    void setAudio(const QString &value);
    QStringList getTranslations() const;
    void setTranslations(const QStringList &value);
};

#endif // WORD_H
