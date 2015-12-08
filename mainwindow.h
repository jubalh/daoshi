#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "word.h"
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
    void onLessonLoaded(QList<Word> wordList);

private:
    Ui::MainWindow *ui;
    void runOpenLessonDialog(void);
};

#endif // MAINWINDOW_H
