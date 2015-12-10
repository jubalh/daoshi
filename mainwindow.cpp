#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opendialog.h"
#include "ui_opendialog.h"
#include "helper.h"
#include <Qt>
#include <QTime>
#include <QMovie>
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

    this->ui->frameOpening->setGeometry(10, 10, this->ui->frameOpening->width(), this->ui->frameOpening->width());
    this->ui->frameLesson->setVisible(false);

    QTime now = QTime::currentTime();
    qsrand(now.msec());
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

void MainWindow::onLessonLoaded(Lesson lesson)
{
   this->mLesson = lesson;
   qDebug() << "Loaded a list containing" << this->mLesson.wordList().count() << "words";

   //Word word = wordList.at( qrand() % wordList.count() );
   Word word = this->mLesson.wordList().at(0);

   this->ui->frameOpening->setVisible(false);
   this->ui->lblPictogram->setText(word.getPictogram());
   this->ui->lblPinyin->setText(word.getPinyin());
   this->ui->lblTranslation->setText(word.getTranslation());
   this->ui->frameLesson->setVisible(true);

   QString pth = this->getPictogramPath(word.getPictogram());

   /*
   QPixmap disp;
   if (disp.load(pth))
   {
       this->ui->lblPictogram->setPixmap(disp);
       this->ui->lblPictogram->setGeometry(0,0,disp.width(), disp.height());
   }
   */

   QSize s(130,130);
   QMovie *movie = new QMovie(pth);
   movie->setScaledSize(s);
   this->ui->lblPictogram->setMovie(movie);
   movie->start();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

QString MainWindow::getPictogramPath(QString pictogram)
{
   return Helper::getLessonPath(this->mLesson.name()) + "/" + pictogram + ".gif";
}
