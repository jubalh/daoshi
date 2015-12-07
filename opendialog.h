#ifndef OPENDIALOG_H
#define OPENDIALOG_H

#include "lessonloader.h"
#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class OpenDialog;
}

class OpenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenDialog(QWidget *parent = 0);
    ~OpenDialog();
    LessonLoader *mLessonLoader;

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void onLessonLoaded();

private:
    Ui::OpenDialog *ui;
};

#endif // OPENDIALOG_H
