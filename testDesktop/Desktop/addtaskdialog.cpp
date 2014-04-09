#include "addtaskdialog.h"
#include "ui_addtaskdialog.h"

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

}

void AddTaskDialog::on_buttonBox_rejected()
{

}
