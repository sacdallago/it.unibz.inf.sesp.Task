#include "taskwidget.h"
#include "ui_taskwidget.h"
#include <QWidget>
#include <QMessageBox>
#include "task.h"


TaskWidget::TaskWidget(QWidget *parent) :
    QWidget(parent),

    ui(new Ui::TaskWidget)
{
    // this->task = task;
    //ui->titleLabel->setText(task.getName());
    //ui->descriptionText->setText(task.getDescription());
    ui->setupUi(this);

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

//Add some panel infos to the Task
void TaskWidget::on_toolButton_clicked()
{

}
