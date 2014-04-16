#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent, Collection *tasks) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{

     this->tasks = tasks;

     ui->setupUi(this);
     refreshList();
     cout << "TaskWidgets added from DB" <<endl;

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshList(){

    taskListArea = new QVBoxLayout(ui->scrollArea);
    QList<Task*> ordered = tasks->getTodoList();

    int elements = ordered.size() ;

    for (Task* t : ordered){
       TaskWidget * wt = new TaskWidget();
        wt->fillWidget(t);
        taskListArea->addWidget(wt);
    }

    QLabel * l = new QLabel("Total tasks:  "+QString::number(elements));
    taskListArea->addWidget(l);
    //taskListArea->update();
    ui->scrollArea->setLayout(taskListArea);

    ui->scrollArea->repaint();

}

void MainWindow::on_actionAdd_Task_triggered()
{
  AddTaskDialog addDialog;
  addDialog.exec();

  refreshList();
}
