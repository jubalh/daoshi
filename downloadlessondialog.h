#ifndef DOWNLOADLESSONDIALOG_H
#define DOWNLOADLESSONDIALOG_H

#include <QDialog>
#include "availablelessonsmodel.h"

namespace Ui {
class DownloadLessonDialog;
}

class DownloadLessonDialog : public QDialog
{
   Q_OBJECT

public:
   explicit DownloadLessonDialog(QWidget *parent = 0);
   ~DownloadLessonDialog();

private:
   Ui::DownloadLessonDialog *ui;
   AvailableLessonsModel *model;
};

#endif // DOWNLOADLESSONDIALOG_H
