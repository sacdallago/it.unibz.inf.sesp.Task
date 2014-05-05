#include "mainwindowtest.h"

MainWindowTest::MainWindowTest(QObject *parent) :
    QObject(parent)
{
}

void MainWindowTest::initTestCase()
{
}

void MainWindowTest::test1()
{
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
}
