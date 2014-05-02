#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <logindialog.h>

using namespace std;
MainWindow::MainWindow(QWidget *parent, Collection *tasks) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{
     this->listype = false;
     this->tasks = tasks;
     this->statusLabel = new QLabel();
     this->basicColor = Qt::blue;
     elements = 0;

     ui->setupUi(this);
     ui->statusbar->addWidget(statusLabel);
     taskListArea = new QVBoxLayout(ui->scrollAreaWidgetContents);

     confirmLogin();
     cout << "\n[GUI] Main Window initialized" <<endl;

}


MainWindow::~MainWindow()
{
    clearList();
    delete ui;

}

void MainWindow::confirmLogin(){
    QString error = "Error! Wrong username or password.\nPlease try again";
    LoginDialog log;
    log.exec();

    while(!tasks->login(log.getUser(), log.getPassword())){

        log.setMessage(&error);
        log.exec();
    }

    user = log.getUser();
    log.close();
    cout << user.toStdString() << endl;
    login();
    refreshList();
}

void MainWindow::login(){

        tasks->populateFromDatabase();

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

/**
 * @brief MainWindow::refreshList refresh the task list on screen from the DB
 */
void MainWindow::refreshList(){

    clearList();

    if(listype){
        ordered = tasks->getDoneList();
    }else{
        ordered = tasks->getTodoList();
    }

    this->elements = ordered.size();

    QPalette pal(palette());
    QColor wtColor;

    for (Task* t : ordered){
        TaskWidget * wt = new TaskWidget(NULL, tasks);
        widgets.append(wt);

        pal.setColor(QPalette::Background, basicColor);
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
    color.setAlpha(90);
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

/**
 * @brief MainWindow::on_actionChange_color_triggered change the basic color palette for the tasks
 */
void MainWindow::on_actionChange_color_triggered()
{
    QColorDialog chooser;
    int result = chooser.exec();

    if(result == 1){
        basicColor = chooser.selectedColor();
        refreshList();
    }
}

/**
 * @brief MainWindow::on_actionLog_in_triggered
 */
void MainWindow::on_actionLog_in_triggered()
{
    confirmLogin();
}

void MainWindow::on_actionAbout_triggered()
{

}

void MainWindow::on_actionView_Done_task_triggered()
{
    listype = true;
    refreshList();
}


void MainWindow::on_actionView_Tdod_Tasks_triggered()
{
    listype = false;
    refreshList();
}
