#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>
#include "task.h"

namespace Ui {
class TaskWidget;
}

class TaskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskWidget(QWidget *parent = 0);
    ~TaskWidget();
    void fillWidget(Task *t);

    qint64 getId() const;
    void setId(qint64 value);

private slots:


    void on_pushButton_3_clicked();

private:
    Ui::TaskWidget *ui;

    qint64 id;

};

#endif // TASKWIDGET_H
