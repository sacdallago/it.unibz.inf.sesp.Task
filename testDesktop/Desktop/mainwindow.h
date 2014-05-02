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
    explicit MainWindow(QWidget *parent = 0, Collection *tasks = new Collection());
    ~MainWindow();
     void refreshList();

private slots:
     /**
     * @brief on_actionAdd_Task_triggered launch add task dialog
     */
    void on_actionAdd_Task_triggered();

    /**
     * @brief on_actionRefresh_2_triggered launch a refresh for the current list
     */
    void on_actionRefresh_2_triggered();

    /**
     * @brief on_actionChange_color_triggered launch a QColorChooser.
     * Allows the user to select the base color on which construct the palette of each task.
     */
    void on_actionChange_color_triggered();

    /**
     * @brief on_actionLog_in_triggered launch log in action and refresh
     */
    void on_actionLog_in_triggered();

    /**
     * @brief on_actionAbout_triggered launches an about box of the program
     */
    void on_actionAbout_triggered();

    /**
     * @brief on_actionView_Done_task_triggered refresh the task list with the "done" tasks
     */
    void on_actionView_Done_task_triggered();

    /**
     * @brief on_actionView_Todo_Tasks_triggered
     */
    void on_actionView_Todo_Tasks_triggered();

    void on_actionView_Tdod_Tasks_triggered();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *taskListArea;
    QLabel *statusLabel;
    QLabel *userLabel;
    QColor basicColor;

    Collection *tasks;
    QString user;
    bool listype;
    QList <Task*> ordered;
    QList <TaskWidget*> widgets;

    int elements;

    /**
     * @brief clearList() clear old task data for refreshing
     */
    void clearList();
    void login();
    void confirmLogin();
    QColor generateRandomColor(QColor mix);

};

#endif // MAINWINDOW_H
