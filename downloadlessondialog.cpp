#include "downloadlessondialog.h"
#include "ui_downloadlessondialog.h"

DownloadLessonDialog::DownloadLessonDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::DownloadLessonDialog)
{
   ui->setupUi(this);

   model = new AvailableLessonsModel();
   ui->tableView->setModel(model);
}

DownloadLessonDialog::~DownloadLessonDialog()
{
   delete ui;
}
