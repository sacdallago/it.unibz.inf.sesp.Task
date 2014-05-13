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
  Fill the widget with the information taken from a Task.
  Delete "done" Button if status is not 0.
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
    if(task->getStatus()!=0){
        delete ui->pushButton;
    }
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
        tasks->removeItem(this->task);
      }
}



/**
  Launch a more/edit menu box, MoreDialog.
 * @brief TaskWidget::on_pushButton_2_clicked
 */
void TaskWidget::on_pushButton_2_clicked()
{
    MoreDialog more (0, tasks);
    more.fillWidget(task);

    int result = more.exec();
    cout << result << endl;
    if(result == 1){

        this->task->setName( more.getTitle());
        this->task->setDescription(more.getDescription());
        this->task->setDurationInH(more.getEffort());
        this->task->setImportance(more.getPriority());

        this->fillWidget(task);
        tasks->update(task);
    }
}

/**
 * @brief TaskWidget::getTask getter for the Task pointer
 * @return
 */
Task *TaskWidget::getTask() const
{
    return task;
}

/**
 * @brief TaskWidget::setTask setter for the Task pointer
 * @param value
 */
void TaskWidget::setTask(Task *value)
{
    task = value;
}

/**
 * @brief TaskWidget::on_pushButton_clicked flag the Task as "Done", status not 0.
 */
void TaskWidget::on_pushButton_clicked()
{
    tasks->done(this->task);
}
