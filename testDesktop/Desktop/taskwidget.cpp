#include "taskwidget.h"
#include "ui_taskwidget.h"

TaskWidget::TaskWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskWidget)
{
    ui->setupUi(this);
}

TaskWidget::~TaskWidget()
{
    delete ui;
}

//Ask confirrmation to delete task
void TaskWidget::on_pushButton_3_clicked()
{

}
