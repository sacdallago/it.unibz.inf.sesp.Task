#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include <QObject>
#include <tests/AutoTest.h>

class MainWindowTest : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowTest(QObject *parent = 0);

signals:

public slots:

private slots:
        void initTestCase();
        void test1();
        void test2();
        void test3();
        void cleanupTestCase();


};

DECLARE_TEST(MainWindowTest)

#endif // MAINWINDOWTEST_H
