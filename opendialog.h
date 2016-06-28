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
    Lesson loadedLesson() const;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::OpenDialog *ui;
    Lesson loaded_lesson;
};

#endif // OPENDIALOG_H
