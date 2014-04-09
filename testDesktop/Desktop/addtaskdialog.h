#ifndef ADDTASKDIALOG_H
#define ADDTASKDIALOG_H

#include <QDialog>

namespace Ui {
class AddTaskDialog;
}

class AddTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskDialog(QWidget *parent = 0);
    ~AddTaskDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_dependsOnComboBox_activated(const QString &arg1);

private:
    Ui::AddTaskDialog *ui;
};

#endif // ADDTASKDIALOG_H
