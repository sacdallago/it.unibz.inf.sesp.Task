#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>
#include "task.h"
#include "collection.h"


namespace Ui {
class TaskWidget;
}

class TaskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskWidget(QWidget *parent = 0, Collection *tasks = new Collection());
    ~TaskWidget();
    void fillWidget(Task *t);

    Task *getTask() const;
    void setTask(Task *value);

private slots:


    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::TaskWidget *ui;

    Task *task;
    Collection *tasks;

};

#endif // TASKWIDGET_H
