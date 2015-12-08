#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opendialog.h"
#include "ui_opendialog.h"
#include <Qt>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QIcon icon(":/images/resources/long.ico");
    this->setWindowIcon(icon);

    QPixmap disp;
    disp.load(":/images/resources/folder-color.svg");
    //disp = disp.scaled(this->ui->pushButton->size());

    this->ui->pushButton->setFlat(true);
    this->ui->pushButton->setText("");
    this->ui->pushButton->setIcon(disp);
    this->ui->pushButton->setFocusPolicy(Qt::NoFocus);
    this->ui->pushButton->setIconSize(this->ui->pushButton->size());
    this->ui->pushButton->setStyleSheet("QPushButton:pressed{ background-color: transparent; }");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::runOpenLessonDialog()
{
    OpenDialog *od = new OpenDialog(this);
    od->exec();
}

void MainWindow::on_actionOpen_Lesson_triggered()
{
    this->runOpenLessonDialog();
}

void MainWindow::on_pushButton_clicked()
{
    this->runOpenLessonDialog();
}

void MainWindow::onLessonLoaded(QList<Word> wordList)
{
   qDebug() << "Loaded a list containing" << wordList.count() << "words";
}
