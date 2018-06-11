#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QMediaPlayer>
#include "word.h"
#include "lesson.h"
#include "checkonline.h"

namespace Ui {
class MainWindow;
}

class QTextBrowser;
enum class VisibleWidget : short { transliteration, translation, note, example, LAST };

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_Lesson_triggered();
    void on_pushButton_clicked();
    void onLessonLoaded(Lesson lesson);
    void on_actionExit_triggered();
    void on_btnNextWord_clicked();
    void on_actionClose_Lesson_triggered();
    void on_btnNextDisplay_clicked();
    void on_actionAbout_triggered();
    void on_btnSpeaker_clicked();
    void on_actionCheckForUpdates_triggered();
    void on_actionDownloadLessons_triggered();
    void on_ucCheckedLatestVersion(QString version);
    void on_ucReceivedAvailLessons(QString text);

private:
    struct WordUi {
       QString value;
       QTextBrowser *ui;
    };
    std::map<VisibleWidget, WordUi> wordparts;
    Lesson mLesson;
    int mCurrentWordIndex;
    QMediaPlayer mPlayer;
    Ui::MainWindow *ui;
    void runOpenLessonDialog(void);
    QString getPictogramPath(QString pictogram);
    void displayWord();
    void chooseRandomWord();
    void toggleLessonMode(bool bMakeLessonActive);
    void saveSettings();
    VisibleWidget current_displayed_widget;
    CheckOnline *updateChecker;
};

#endif // MAINWINDOW_H
