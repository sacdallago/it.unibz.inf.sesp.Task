#include "taskwidget.h"
#include "ui_taskwidget.h"
#include <QWidget>
#include <QMessageBox>
#include "task.h"
#include <iostream>

using namespace std;

TaskWidget::TaskWidget(QWidget *parent) :
    QWidget(parent),

    ui(new Ui::TaskWidget)
{
    // this->task = task;
    //ui->titleLabel->setText(task.getName());
    //ui->descriptionText->setText(task.getDescription());
    ui->setupUi(this);


}

void TaskWidget::fillWidget(Task *t)
{ ui->titleLabel->setText(t->getName());
    ui->descriptionText->setText(t->getDescription());
    QString priority;
    priority.append(QString("%1").arg(t->getImportance()));
    ui->priorityLabel->setText(priority);
    QString effort;
    effort.append(QString("%1").arg(t->getDurationInH()));
    ui->effortValueLabel->setText(effort);

    this->id = t->getId();
}

TaskWidget::~TaskWidget()
{
    delete ui;
}

//Ask confirmation to delete task
void TaskWidget::on_pushButton_3_clicked()
{

    QMessageBox confirm;
    confirm.exec();

}
qint64 TaskWidget::getId() const
{
    return id;
}

void TaskWidget::setId(qint64 value)
{
    id = value;
}


