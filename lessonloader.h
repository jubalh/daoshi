#ifndef LESSONLOADER_H
#define LESSONLOADER_H

#include <QThread>

class LessonLoader : public QThread
{
    Q_OBJECT
private:
    bool checkLessonStructure();
    QString mLessonName;
public:
    explicit LessonLoader(QObject *parent = 0);
    void run();
    void setLessonName(QString name);

signals:
    bool loaded();

public slots:

};

#endif // LESSONLOADER_H
