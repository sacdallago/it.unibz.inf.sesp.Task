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
    explicit TaskWidget(QWidget *parent = 0, Collection *tasks = new Collection(), MainWindow *main = new MainWindow());
    ~TaskWidget();
    void fillWidget(Task *t);

    Task *getTask();
    void setTask(Task *value);

    MainWindow *getMain() const;
    void setMain(MainWindow *value);

private slots:


    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TaskWidget *ui;

    Task *task;
    Collection *tasks;
    MainWindow *main;

};

#endif // TASKWIDGET_H
