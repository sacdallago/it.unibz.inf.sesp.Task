#include "widget.h"
#include <iostream>
#include <QApplication>
#include <mainwindow.h>
#include <collection.h>

int main(int argc, char *argv[]) {

        QApplication a(argc, argv);
        Collection tasks;

        MainWindow w (0, &tasks);
        w.show();
        w.confirmLogin();

        return a.exec();


}
