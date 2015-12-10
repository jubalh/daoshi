#include "opendialog.h"
#include "ui_opendialog.h"
#include <QDir>
#include <QDebug>
#include "helper.h"
#include "lesson.h"

OpenDialog::OpenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenDialog)
{
    ui->setupUi(this);
    qRegisterMetaType<Lesson>("Lesson");

    QDir dir(Helper::getLessonsDirectory());
    QStringList lessons = dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot);

    ui->listWidget->addItems(lessons);

    mLessonLoader = new LessonLoader(this);
    connect(mLessonLoader, SIGNAL(loaded(Lesson)), this->parent(), SLOT(onLessonLoaded(Lesson)));
}

OpenDialog::~OpenDialog()
{
    delete ui;
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
