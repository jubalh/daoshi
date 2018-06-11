#ifndef DOWNLOADLESSONDIALOG_H
#define DOWNLOADLESSONDIALOG_H

#include <QDialog>
#include "availablelessonsmodel.h"
#include "onlinelesson.h"

namespace Ui {
class DownloadLessonDialog;
}

class DownloadLessonDialog : public QDialog
{
   Q_OBJECT

public:
   explicit DownloadLessonDialog(QWidget *parent = 0);
   ~DownloadLessonDialog();
   void setLessons(const QList<OnlineLesson> &value);

private:
   Ui::DownloadLessonDialog *ui;
   AvailableLessonsModel *model;
   QList<OnlineLesson> lessons;

private slots:
   void updateDescription();
};

#endif // DOWNLOADLESSONDIALOG_H
