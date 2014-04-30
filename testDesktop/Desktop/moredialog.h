#ifndef MOREDIALOG_H
#define MOREDIALOG_H

#include <QDialog>
#include "taskwidget.h"
#include <QVBoxLayout>

namespace Ui {
class MoreDialog;
}

class MoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoreDialog(QWidget *parent = 0, TaskWidget *wt = new TaskWidget());
    ~MoreDialog();

    TaskWidget *getWt() const;
    void setWt(TaskWidget *value);
     void fillWidget(Task *t);

     Ui::MoreDialog *getUi() const;
     void setUi(Ui::MoreDialog *value);

     QString getTitle() const;
     QString getDescription() const;
     qint64  getPriority() const;
     qint64  getEffort() const;

private:
     Ui::MoreDialog *ui;
     TaskWidget *wt;
     QVBoxLayout *lslayout;

    QList<Task *> *dlist;

    void getDependList();

};

#endif // MOREDIALOG_H
