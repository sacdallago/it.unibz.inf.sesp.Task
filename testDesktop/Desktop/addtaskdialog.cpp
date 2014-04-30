#include "addtaskdialog.h"
#include "ui_addtaskdialog.h"
#include "task.h"
#include "taskwidget.h"
#include "mainwindow.h"
#include "collection.h"
#include "connection.h"
#include "taskutilities.h"


AddTaskDialog::AddTaskDialog(QWidget *parent, Collection* coll) :
    QDialog(parent),
    ui(new Ui::AddTaskDialog)
{   //Setup the gui
    ui->setupUi(this);
    this->coll=coll;
}

AddTaskDialog::~AddTaskDialog()
{
    delete ui;
}

//Here goes code for adding Task and refresh
void AddTaskDialog::on_buttonBox_accepted()
{

    //Creation of the task
    Task newTask(0,
              ui->prioritySpinBox->text().toInt(),
              ui->effortSpinBox->text().toInt(),
              ui->nameLineEdit->text(),
              ui->plainTextEdit->toPlainText());

    //Inset the task into the DB
    coll->addItem(newTask.getName(),
                          newTask.getImportance(),
                          newTask.getDurationInH(),
                          newTask.getDescription(),
                          1);
}

void AddTaskDialog::on_buttonBox_rejected()
{

}

//Generate a list of available Task for dependencies
void AddTaskDialog::on_dependsOnComboBox_activated(const QString &arg1)
{

}
