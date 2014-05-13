#include <iostream>
#include <QApplication>
#include <mainwindow.h>
#include <collection.h>
#include <tests/AutoTest.h>
#include <QDebug>


int main(int argc, char *argv[]) {

    //Run all the tests
    int failures = AutoTest::run(argc, argv);
        if (failures == 0)

        {
            qDebug() << "ALL TESTS PASSED";
        }
        else
        {
            qDebug() << failures << " TESTS FAILED!";
        }


    //Run the application
        QApplication a(argc, argv);
        Collection tasks;

        MainWindow w (0, &tasks);
        w.show();
        w.confirmLogin();

        return a.exec();
}
