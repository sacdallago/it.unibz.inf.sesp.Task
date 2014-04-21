#include "taskwidget.h"
#include "ui_taskwidget.h"
#include <QWidget>
#include <QMessageBox>
#include "task.h"
#include <iostream>
#include <collection.h>

using namespace std;

TaskWidget::TaskWidget(QWidget *parent ,Collection *tasks) :
    QWidget(parent),

    ui(new Ui::TaskWidget)
{

    this->tasks = tasks;
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

    this->task = t;
}

TaskWidget::~TaskWidget()
{
    delete ui;
}

//Ask confirmation to delete task
void TaskWidget::on_pushButton_3_clicked()
{

    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Confirm", "Delete Task?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        cout << "Yes was clicked" << endl;
        //cout << "Deleting task n: " << this->task->getId() << " Name: " << this->task->getName() << endl;
        tasks->removeItem(this->task);

      } else {
        cout << "Yes was *not* clicked";
      }
}





