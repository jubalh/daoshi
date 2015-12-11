#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "word.h"
#include "lesson.h"
#include <QMainWindow>
#include <QList>

namespace Ui {
class MainWindow;
}

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

private:
    Lesson mLesson;
    Ui::MainWindow *ui;
    void runOpenLessonDialog(void);
    QString getPictogramPath(QString pictogram);
    void displayWord(Word word);
    void displayRandomWord();
    void toggleMode();
    bool makeVisible(QWidget *widget);
};

#endif // MAINWINDOW_H
