#include "opendialog.h"
#include "ui_opendialog.h"
#include "helper.h"
#include "lesson.h"
#include <QDir>
#include <QTextEdit>
#include <QDebug>

OpenDialog::OpenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenDialog)
{
    ui->setupUi(this);
    qRegisterMetaType<Lesson>("Lesson");

    QDir dir(Helper::getLessonsDirectory());
    QStringList lessons = dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot);

    if(lessons.empty())
    {
        QTextEdit *infoEdit = new QTextEdit(this);
        infoEdit->setGeometry(this->ui->listWidget->geometry());
        infoEdit->setText("No lessons installed");
        infoEdit->setEnabled(false);
        infoEdit->setVisible(true);
        this->ui->listWidget->setVisible(false);
    }
    else
    {
        ui->listWidget->addItems(lessons);

        this->ui->listWidget->setCurrentRow(0);
    }
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
        LessonLoader lessonLoader;
        loaded_lesson = lessonLoader.loadLesson(name);
    }
}

Lesson OpenDialog::loadedLesson() const
{
   return loaded_lesson;
}
