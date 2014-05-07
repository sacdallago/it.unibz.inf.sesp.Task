#include "mainwindowtest.h"

MainWindowTest::MainWindowTest(QObject *parent) :
    QObject(parent)
{

}

void MainWindowTest::initTestCase()

{
    /**
    QApplication a();
    main = new MainWindow(0, coll);
    main->show();
    a.exec();
    **/
}

void MainWindowTest::test1()
{
    /**
    main->confirmLogin();
    **/
    QVERIFY(1 + 1 == 2);
}

void MainWindowTest::test2()
{
    QVERIFY(1 == 0);
}

void MainWindowTest::test3()
{

}

void MainWindowTest::cleanupTestCase()
{
    /**
    delete &main;
    delete &coll;
    **/
}
