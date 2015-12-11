#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opendialog.h"
#include "ui_opendialog.h"
#include "helper.h"
#include <Qt>
#include <QTime>
#include <QMovie>
#include <QMessageBox>
#include <QSettings>
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
    this->ui->btnNextWord->setToolTip("Next word");

    QPixmap dispDownArrow;
    dispDownArrow.load(":/images/resources/down-arrow.svg");
    this->ui->btnNextDisplay->setIcon(dispDownArrow);
    this->ui->btnNextDisplay->setIconSize(this->ui->btnNextDisplay->size());
    this->ui->btnNextDisplay->setToolTip("Show next field");

    QPixmap dispSpeaker;
    dispSpeaker.load(":images/resources/speaker.svg");
    this->ui->btnSpeaker->setIcon(dispSpeaker);
    this->ui->btnSpeaker->setIconSize(this->ui->btnSpeaker->size());
    this->ui->btnSpeaker->setToolTip("Play audio");

    this->toggleLessonMode(false);

    QString sTbStyle("QTextBrowser{ background-color: transparent; }");
    this->ui->tbTranslation->setStyleSheet(sTbStyle);
    this->ui->tbNote->setStyleSheet(sTbStyle);
    this->ui->tbExample->setStyleSheet(sTbStyle);
    this->ui->tbTransliteration->setStyleSheet(sTbStyle);

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
   qDebug() << "Loaded lesson" << this->mLesson.name() <<
               "containing" << this->mLesson.wordList().count() <<
               "words" << "in version " << this->mLesson.version();

   this->toggleLessonMode(true);

   QSettings setting("jubalh", "daoshi");
   setting.beginGroup("WindowLesson");
   QRect position = setting.value("Position").toRect();
   this->setGeometry(position);
   setting.endGroup();

   this->displayRandomWord();
}

void MainWindow::displayWord(Word word)
{
   this->ui->tbTransliteration->setVisible(false);
   this->ui->tbTranslation->setVisible(false);
   this->ui->tbNote->setVisible(false);
   this->ui->tbExample->setVisible(false);

   this->ui->lblPictogram->setText(word.getPictogram());
   this->ui->tbTransliteration->setText(word.getPinyin());
   this->ui->tbNote->setText(word.getNote());

//   this->ui->tbTranslation->setText(word.getTranslation());

   this->ui->tbTranslation->setHtml(  Helper::stringListToHtml(word.getTranslations()) );
   this->ui->tbExample->setHtml(  Helper::stringListToHtml(word.getExampleSentences()) );

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

   QString audio = word.getAudio();
   if (audio.isEmpty())
   {
       this->ui->btnSpeaker->setEnabled(false);
       this->ui->btnSpeaker->setToolTip("No audio available");
   }
   else
   {
       this->ui->btnSpeaker->setEnabled(true);
       this->ui->btnSpeaker->setToolTip("Play audio");
       QString audioPath = Helper::getLessonPath(this->mLesson.name()) + "/" + audio;
       this->mPlayer.setMedia(QUrl::fromLocalFile(audioPath));
   }
}

void MainWindow::displayRandomWord()
{
   Word word = this->mLesson.wordList().at(qrand() % this->mLesson.wordList().count());
   //Word word = this->mLesson.wordList().at(0);
   this->displayWord(word);
}

void MainWindow::on_actionExit_triggered()
{
    this->saveSettings();
    QApplication::quit();
}

QString MainWindow::getPictogramPath(QString pictogram)
{
   return Helper::getLessonPath(this->mLesson.name()) + "/" + pictogram + ".gif";
}

void MainWindow::on_btnNextWord_clicked()
{
    this->displayRandomWord();
    if(this->mPlayer.state() == QMediaPlayer::PlayingState)
        this->mPlayer.stop();
}

void MainWindow::toggleLessonMode(bool bMakeLessonActive)
{
    if (bMakeLessonActive)
    {
        // show lesson window
        this->ui->pgOpenLesson->setVisible(false);
        this->ui->pgDisplayLesson->setVisible(true);
        this->setFixedSize(740, 640);
        this->ui->actionClose_Lesson->setEnabled(true);
    }
    else
    {
        // show open window
        this->ui->pgOpenLesson->setVisible(true);
        this->ui->pgDisplayLesson->setVisible(false);
        this->setFixedSize(600, 380);
        this->ui->actionClose_Lesson->setEnabled(false);
    }
}

void MainWindow::on_actionClose_Lesson_triggered()
{
    this->toggleLessonMode(false);
}

bool MainWindow::makeVisible(QWidget *widget)
{
    // already visible, skip this on
    if(widget->isVisible())
        return true;

    // wdget is empty, skip this one
    if(QString::compare(widget->metaObject()->className(), "QLabel") == 0)
    {
        QLabel* lbl = (QLabel*)widget;
        if(lbl->text().isEmpty())
            return true;
    } else if(QString::compare(widget->metaObject()->className(), "QTextBrowser") == 0)
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
    if(makeVisible(this->ui->tbTransliteration))
        if(makeVisible(this->ui->tbTranslation))
            if(makeVisible(this->ui->tbNote))
                makeVisible(this->ui->tbExample);
}

void MainWindow::saveSettings()
{
   QSettings setting("jubalh", "daoshi");
   setting.beginGroup("WindowLesson");
   setting.setValue("Position", this->geometry());
   setting.endGroup();
   setting.beginGroup("Lesson");
   setting.setValue("LastLesson", this->mLesson.name());
   setting.endGroup();
}

void MainWindow::on_actionAbout_triggered()
{
   QMessageBox::about(this, "About", "<b>Daoshi</b><br><br>Daoshi is a vocabulary trainer targetting Chinese and other languages with foreign scripts.");
}

void MainWindow::on_btnSpeaker_clicked()
{
   this->mPlayer.play();
}
