#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connection.h"
#include "addtaskdialog.h"
#include "collection.h"
#include "taskutilities.h"
#include "taskwidget.h"
#include <QtWidgets>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, Collection *tasks = new Collection() );
    ~MainWindow();
     void refreshList();

private slots:
    void on_actionAdd_Task_triggered();

    void on_actionRefresh_2_triggered();

    void on_actionChange_color_triggered();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *taskListArea;
    QLabel *statusLabel;
    QColor basicColor;

    Collection *tasks;
    QList <Task*> ordered;
    QList <TaskWidget*> widgets;

    int elements;


    void clearList();
    QColor generateRandomColor(QColor mix);

};

#endif // MAINWINDOW_H
