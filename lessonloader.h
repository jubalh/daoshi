#ifndef LESSONLOADER_H
#define LESSONLOADER_H

#include <QThread>

class LessonLoader : public QThread
{
    Q_OBJECT
public:
    explicit LessonLoader(QObject *parent = 0);

signals:

public slots:

};

#endif // LESSONLOADER_H
