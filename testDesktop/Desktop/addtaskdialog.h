#ifndef ADDTASKDIALOG_H
#define ADDTASKDIALOG_H

#include "collection.h"
#include <QDialog>

namespace Ui {
class AddTaskDialog;
}

class AddTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskDialog(QWidget *parent = 0, Collection *coll = NULL);
    ~AddTaskDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddTaskDialog *ui;
    Collection* coll;
};

#endif // ADDTASKDIALOG_H
