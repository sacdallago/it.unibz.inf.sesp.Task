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

private slots:
    void on_actionAdd_Task_triggered();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *taskListArea;
    QLabel *statusLabel;

    Collection *tasks;
    QList <Task*> ordered;

    int elements;

    void refreshList();
    QColor generateRandomColor(QColor mix);

};

#endif // MAINWINDOW_H
