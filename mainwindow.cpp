#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opendialog.h"
#include "ui_opendialog.h"
#include "helper.h"
#include <Qt>
#include <QTime>
#include <QMovie>
#include <QMessageBox>
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

    QPixmap dispNextArrow;
    dispNextArrow.load(":/images/resources/next-arrow.svg");
    this->ui->btnNextWord->setIcon(dispNextArrow);
    this->ui->btnNextWord->setIconSize(this->ui->btnNextWord->size());

    QPixmap dispDownArrow;
    dispDownArrow.load(":/images/resources/down-arrow.svg");
    this->ui->btnNextDisplay->setIcon(dispDownArrow);
    this->ui->btnNextDisplay->setIconSize(this->ui->btnNextDisplay->size());

    this->ui->pgOpenLesson->setVisible(true);
    this->ui->pgDisplayLesson->setVisible(false);
    this->resize(600, 380);

    Helper::createPaths();

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
   if (!lesson.error().isEmpty())
   {
       QMessageBox::warning(this, "Error", lesson.error());
       return;
   }

   this->mLesson = lesson;
   qDebug() << "Loaded a list containing" << this->mLesson.wordList().count() << "words";

   this->toggleMode();

   this->displayRandomWord();
}

void MainWindow::displayWord(Word word)
{
   this->ui->lblPinyin->setVisible(false);
   this->ui->lblTranslation->setVisible(false);
   this->ui->lblNote->setVisible(false);
   this->ui->tbExample->setVisible(false);

   this->ui->lblPictogram->setText(word.getPictogram());
   this->ui->lblPinyin->setText(word.getPinyin());
   this->ui->lblTranslation->setText(word.getTranslation());
   this->ui->lblNote->setText(word.getNote());
   this->ui->tbExample->setText(word.getExampleSentences().join("\n"));

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

void MainWindow::displayRandomWord()
{
   Word word = this->mLesson.wordList().at(qrand() % this->mLesson.wordList().count());
   //Word word = this->mLesson.wordList().at(0);
   this->displayWord(word);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

QString MainWindow::getPictogramPath(QString pictogram)
{
   return Helper::getLessonPath(this->mLesson.name()) + "/" + pictogram + ".gif";
}

void MainWindow::on_btnNextWord_clicked()
{
    this->displayRandomWord();
}

void MainWindow::toggleMode()
{
    if (this->ui->pgOpenLesson->isVisible())
    {
        this->ui->pgOpenLesson->setVisible(false);
        this->ui->pgDisplayLesson->setVisible(true);
        this->resize(740, 640);
    }
    else
    {
        this->ui->pgOpenLesson->setVisible(true);
        this->ui->pgDisplayLesson->setVisible(false);
        this->resize(600, 380);
    }
}

void MainWindow::on_actionClose_Lesson_triggered()
{
    this->toggleMode();
}

bool MainWindow::makeVisible(QWidget *widget)
{
    // already visible, skit this on
    if(widget->isVisible())
        return true;

    // wdget is empty, skip this one
    if(QString::compare(widget->metaObject()->className(), "QLabel") == 0)
    {
        QLabel* lbl = (QLabel*)widget;
        if(lbl->text().isEmpty())
            return true;
    } else if(QString::compare(widget->metaObject()->className(), "QTextEdit") == 0)
    {
        QTextBrowser* te = (QTextBrowser*)widget;
        if (te->toPlainText().isEmpty())
            return true;
    }

    // set visible
    widget->setVisible(true);
    return false;
}

void MainWindow::on_btnNextDisplay_clicked()
{
    // test which widget is visible and make the next one visible
    if(makeVisible(this->ui->lblPinyin))
        if(makeVisible(this->ui->lblTranslation))
            if(makeVisible(this->ui->lblNote))
                makeVisible(this->ui->tbExample);
}
