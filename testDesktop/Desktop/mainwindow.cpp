#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent, Collection *tasks) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{

     this->tasks = tasks;
     this->statusLabel = new QLabel();
     elements = 0;

     ui->setupUi(this);
     ui->statusbar->addWidget(statusLabel);
     taskListArea = new QVBoxLayout(ui->scrollAreaWidgetContents);

     refreshList();
     cout << "TaskWidgets added from DB" <<endl;

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshList(){


    if(elements != 0){
        delete taskListArea;
        taskListArea = new QVBoxLayout(ui->scrollAreaWidgetContents);
        ordered.clear();
        }

        ordered = tasks->getTodoList();
        this->elements = ordered.size();

    /*
    QPalette pal(palette());
    QColor wtColor;
    */

    for (Task* t : ordered){
       TaskWidget * wt = new TaskWidget(NULL, tasks);

       /*
       pal.setColor(QPalette::Background, Qt::blue);
       wt->setAutoFillBackground(true);
       wtColor = generateRandomColor(pal.color(QPalette::Background));
       pal.setColor(QPalette::Background, wtColor);
       wt->setPalette(pal);
       */

       wt->fillWidget(t);
       taskListArea->addWidget(wt);
    }

    statusLabel->setText("Total tasks:  "+QString::number(elements));

    ui->scrollArea->repaint();
    ui->statusbar->repaint();

}

QColor generateRandomColor(QColor mix) {
    int red = qrand();
    int green = qrand();
    int blue = qrand();

    // mix the color
    if (mix.isValid()) {
        red = (red + mix.red()) / 2;
        green = (green + mix.green()) / 2;
        blue = (blue + mix.blue()) / 2;
    }

    QColor color;
    color.setRgb(red, green, blue);
    return color;
}


void MainWindow::on_actionAdd_Task_triggered()
{
  AddTaskDialog addDialog;
  addDialog.exec();

  refreshList();
}
