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

void MainWindow::clearList(){

    if(elements != 0){
        delete taskListArea;
        taskListArea = new QVBoxLayout(ui->scrollAreaWidgetContents);
        ordered.clear();
        foreach(TaskWidget* wt, widgets){
            delete wt;
        }
        widgets.clear();
        }
}

void MainWindow::refreshList(){

    clearList();

    ordered = tasks->getTodoList();
    this->elements = ordered.size();


    QPalette pal(palette());
    QColor wtColor;


    for (Task* t : ordered){
        TaskWidget * wt = new TaskWidget(NULL, tasks);
        widgets.append(wt);

        pal.setColor(QPalette::Background, Qt::blue);
        wt->setAutoFillBackground(true);
        wtColor = generateRandomColor(pal.color(QPalette::Background));
        pal.setColor(QPalette::Background, wtColor);
        wt->setPalette(pal);

        wt->fillWidget(t);
        taskListArea->addWidget(wt);
    }

    statusLabel->setText("Total tasks:  "+QString::number(elements));

    ui->scrollArea->repaint();
    ui->scrollAreaWidgetContents->repaint();
    ui->statusbar->repaint();

}

/**
 * @brief MainWindow::generateRandomColor generates random color from a starting color
 * @param QColor mix
 * @return QColor color
 */
QColor MainWindow::generateRandomColor(QColor mix) {
    int min = 0;
    int max = 256;
    int red = min + ( std::rand() % ( max - min + 1 ) );
    int green = min + ( std::rand() % ( max - min + 1 ) );
    int blue = min + ( std::rand() % ( max - min + 1 ) );

    // mix the color
    if (mix.isValid()) {
        red = (red + mix.red()) / 2;
        green = (green + mix.green()) / 2;
        blue = (blue + mix.blue()) / 2;
    }

    QColor color;
    color.setRgb(red, green, blue);
    color.setAlpha(80);
    return color;
}

/**
 * @brief MainWindow::on_actionAdd_Task_triggered action tigger to add a new Task
 */
void MainWindow::on_actionAdd_Task_triggered()
{
    AddTaskDialog addDialog;
    addDialog.exec();

    refreshList();
}

/**
 * @brief MainWindow::on_actionRefresh_2_triggered action trigger to Refresh the widget List
 */
void MainWindow::on_actionRefresh_2_triggered()
{
    refreshList();
}
