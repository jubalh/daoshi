#include "downloadlessondialog.h"
#include "ui_downloadlessondialog.h"
#include <QDebug>

DownloadLessonDialog::DownloadLessonDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::DownloadLessonDialog)
{
   ui->setupUi(this);
   connect(ui->tableView, &QTableView::activated, this, &DownloadLessonDialog::updateDescription);
}

DownloadLessonDialog::~DownloadLessonDialog()
{
   delete ui;
}

void DownloadLessonDialog::setLessons(const QList<OnlineLesson> &value)
{
   lessons = value;
   model = new AvailableLessonsModel(lessons);
   ui->tableView->setModel(model);
}

void DownloadLessonDialog::updateDescription()
{
   qDebug() << "TRIGGERED";
}
