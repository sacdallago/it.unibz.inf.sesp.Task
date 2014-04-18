#include "widget.h"
#include "collection.h"
#include "connection.h"
#include "taskutilities.h"
#include "mainwindow.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[]) {
    try{
        QApplication a(argc, argv);

        Collection tasks;

        QMap<QString, QList<QVariant>* > taskslist = tasks.getConnection()->select("task");
        QMap<QString, QList<QVariant>* > relations = tasks.getConnection()->select("relation");

        TaskUtilities::tasksFromQuery(&tasks, &taskslist);
        TaskUtilities::relateFromQuery(&tasks, &relations);
        MainWindow w (0, &tasks);
        w.show();
        return a.exec();
    } catch (int i){
        return 1;
    }
    return 0;
}
