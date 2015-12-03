#include "opendialog.h"
#include "ui_opendialog.h"
#include <QDir>
#include <QStandardPaths>
#include <QDebug>

OpenDialog::OpenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenDialog)
{
    ui->setupUi(this);

    QString lessonsPath =  QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) +  "/lessons";
    QDir dir(lessonsPath);
    QStringList lessons = dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot);

    ui->listWidget->addItems(lessons);
}

OpenDialog::~OpenDialog()
{
    delete ui;
}
