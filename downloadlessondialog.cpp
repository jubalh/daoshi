#include "downloadlessondialog.h"
#include "ui_downloadlessondialog.h"

DownloadLessonDialog::DownloadLessonDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::DownloadLessonDialog)
{
   ui->setupUi(this);
}

DownloadLessonDialog::~DownloadLessonDialog()
{
   delete ui;
}
