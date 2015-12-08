#include "opendialog.h"
#include "ui_opendialog.h"
#include <QDir>
#include <QDebug>
#include "helper.h"

OpenDialog::OpenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenDialog)
{
    ui->setupUi(this);
    qRegisterMetaType< QList<Word> >("QList<Word>");

    QDir dir(Helper::getLessonsPath());
    QStringList lessons = dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot);

    ui->listWidget->addItems(lessons);

    mLessonLoader = new LessonLoader(this);
    connect(mLessonLoader, SIGNAL(loaded(QList<Word>)), this->parent(), SLOT(onLessonLoaded(QList<Word>)));
}

OpenDialog::~OpenDialog()
{
    delete ui;
}

void OpenDialog::on_buttonBox_clicked(QAbstractButton *button)
{
}

void OpenDialog::on_buttonBox_accepted()
{
    if (this->ui->listWidget->selectedItems().count() > 0)
    {
        QString name = this->ui->listWidget->selectedItems().at(0)->text();
        qDebug() <<  name;
        mLessonLoader->setLessonName(name);
        mLessonLoader->start();
    }
}
