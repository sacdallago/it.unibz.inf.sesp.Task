#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addtaskdialog.h"
#include <QtWidgets/QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_Task_triggered()
{
  AddTaskDialog addDialog;
  addDialog.exec();

}
