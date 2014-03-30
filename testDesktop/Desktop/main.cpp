#include "widget.h"
#include "task.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[]) {
    //QApplication a(argc, argv);
    //Widget w;
    //w.show();



    //      TEST AREA
    using namespace std;
    Task t, p;
    t.id = 12232;
    t.durationInH = 2;
    t.importance = 4;
    t.name = "Write report";
    t.description = "French report on SESP!";
    t.status = Status::ACTIVE;
    t.relatives = Relatives::ROOT;
    string t1 = printTask(t).toUtf8().constData();
    cout << t1 << endl;
    string p1 = printTask(p).toUtf8().constData();
    cout << p1 << endl;
    cout << "OK" << endl;
    return 0;
    //      END OF TEST AREA




    //return a.exec();
}
