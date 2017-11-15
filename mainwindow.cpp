#include <Qt>
#include <QTime>
#include <QMovie>
#include <QMessageBox>
#include <QSettings>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opendialog.h"
#include "ui_opendialog.h"
#include "helper.h"
#include "version.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QIcon icon(":/images/resources/long.ico");
    this->setWindowIcon(icon);

    QPixmap disp;
    disp.load(":/images/resources/folder-color.svg");

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

    updateChecker = new CheckOnline(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::runOpenLessonDialog()
{
    OpenDialog od;
    if (od.exec() == QDialog::Accepted)
    {
       onLessonLoaded(od.loadedLesson());
    }
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

   this->chooseRandomWord();
}

void MainWindow::displayWord()
{
   // clear
   current_displayed_widget = VisibleWidget::transliteration;
   this->ui->lblPictogram->clear();
   this->ui->tbTransliteration->clear();
   this->ui->tbTranslation->clear();
   this->ui->tbNote->clear();
   this->ui->tbExample->clear();

   // get new word
   Word word = mLesson.wordList().at(mCurrentWordIndex);

   wordparts = {
      {VisibleWidget::transliteration, {word.getPinyin(), ui->tbTransliteration}},
      {VisibleWidget::translation, {Helper::stringListToHtml(word.getTranslations()),ui->tbTranslation}},
      {VisibleWidget::note, {word.getNote(), ui->tbNote}},
      {VisibleWidget::example, {Helper::stringListToHtml(word.getExampleSentences()), ui->tbExample}}
   };

   // set pictogram
   QString pth = this->getPictogramPath(word.getPictogram());

   QSize s(130,130);
   QMovie *movie = new QMovie(pth);
   movie->setScaledSize(s);
   this->ui->lblPictogram->setMovie(movie);
   movie->start();

   // set audio
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

void MainWindow::chooseRandomWord()
{
   mCurrentWordIndex = qrand() % mLesson.wordList().count();
   this->displayWord();
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
    this->chooseRandomWord();
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

void MainWindow::on_btnNextDisplay_clicked()
{
   Word word = mLesson.wordList().at(mCurrentWordIndex);

   forever {
      auto it = wordparts.find(current_displayed_widget);
      if (it == wordparts.end())
         break;

      const WordUi &word = it->second;

      current_displayed_widget = (VisibleWidget)((int)current_displayed_widget + 1);

      if (!word.value.isEmpty()) {
         word.ui->setHtml(word.value);
         break;
      }
   }
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
   QMessageBox::about(this, "About", "<b>Daoshi</b> " VERSION "<br><br>Daoshi is a vocabulary trainer targetting Chinese and other languages with foreign scripts.");
}

void MainWindow::on_btnSpeaker_clicked()
{
   this->mPlayer.play();
}

void MainWindow::on_ucCheckedLatestVersion(QString version)
{
   QMessageBox::information(this, "Check for udpates" , "You run version " VERSION " and the latest one available is " + version);
}

void MainWindow::on_actionCheckForUpdates_triggered()
{
   connect(updateChecker, &CheckOnline::checkedLatestVersion, this, &MainWindow::on_ucCheckedLatestVersion);
   updateChecker->updateAvailable();
}

void MainWindow::on_actionDownloadLessons_triggered()
{
   //TODO: connect signal to a slot that displays available lessons
   updateChecker->getAvailableOnlineLessons();
}
