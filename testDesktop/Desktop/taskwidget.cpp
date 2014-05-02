#include "taskwidget.h"
#include "ui_taskwidget.h"
#include <QWidget>
#include <QMessageBox>
#include "task.h"
#include <iostream>
#include <collection.h>
#include "moredialog.h"

using namespace std;

/**
  Constructor
 * @brief TaskWidget::TaskWidget
 * @param parent
 * @param tasks
 */
TaskWidget::TaskWidget(QWidget *parent , Collection *tasks) :
    QWidget(parent),

    ui(new Ui::TaskWidget)
{
    this->tasks = tasks;
    ui->setupUi(this);


}

/**
  Fill the widget with the information taken from a Task
 * @brief TaskWidget::fillWidget
 * @param t
 */
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

/**
 * @brief TaskWidget::on_pushButton_3_clicked
 *        Ask confirmation and then delete a Task from the Collection
 */
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



/**
  Launch a more/edit menu box, MoreDialog.
 * @brief TaskWidget::on_pushButton_2_clicked
 */
void TaskWidget::on_pushButton_2_clicked()
{
    MoreDialog more;
    more.fillWidget(task);

    int result = more.exec();
    cout << result << endl;
    if(result == 1){

        this->task->setName( more.getTitle());
        this->task->setDescription(more.getDescription());
        if(more.getEffort() != NULL){
            this->task->setDurationInH(more.getEffort());
        }

        if(more.getPriority() != NULL){
            this->task->setImportance(more.getPriority());
        }
        cout << "Task updated: " << endl;
        QString newt = this->task->printTask();
        cout <<  newt.toStdString() << endl;
        this->fillWidget(task);
        tasks->update(task);

    }
}

Task *TaskWidget::getTask() const
{
    return task;
}

void TaskWidget::setTask(Task *value)
{
    task = value;
}


void TaskWidget::on_pushButton_clicked()
{
    tasks->done(this->task);
}
