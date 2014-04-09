#include "addtaskdialog.h"
#include "ui_addtaskdialog.h"
#include "task.h"
#include "taskwidget.h"
#include "mainwindow.h"

AddTaskDialog::AddTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTaskDialog)
{
    ui->setupUi(this);
}

AddTaskDialog::~AddTaskDialog()
{
    delete ui;
}

//Here goes code for adding Task and refresh
void AddTaskDialog::on_buttonBox_accepted()
{
 Task newTask;
 TaskWidget newTaskWidget;
 //return newTask;
}

void AddTaskDialog::on_buttonBox_rejected()
{

}

//Generate a list of available Task for dependencies
void AddTaskDialog::on_dependsOnComboBox_activated(const QString &arg1)
{

}
