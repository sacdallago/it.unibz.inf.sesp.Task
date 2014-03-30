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
    Task a, b, c, d, e ,f;

    //Tasks get loaded from DATABASE

    a.id = 1;
    b.id = 2;
    c.id = 3;
    d.id = 4;
    e.id = 5;
    f.id = 6;

    a.name = "a";
    b.name = "b";
    c.name = "c";
    d.name = "d";
    e.name = "e";
    f.name = "f";

    //Dependencies get loaded from DATABASE
    if (formsCycle(&a,&b)){
        cout <<  "Forms cycle!" << endl;
    } else {
        cout <<  "Doesn't form cycle!" << endl;
        relate(&a,&b);
    }
    if (formsCycle(&a,&c)){
        cout <<  "Forms cycle!" << endl;
    } else {
        cout <<  "Doesn't form cycle!" << endl;
        relate(&a,&c);
    }
    if (formsCycle(&c,&e)){
        cout <<  "Forms cycle!" << endl;
    } else {
        cout <<  "Doesn't form cycle!" << endl;
        relate(&c,&e);
    }
    if (formsCycle(&c,&f)){
        cout <<  "Forms cycle!" << endl;
    } else {
        cout <<  "Doesn't form cycle!" << endl;
        relate(&c,&f);
    }
    if (formsCycle(&d,&f)){
        cout <<  "Forms cycle!" << endl;
    } else {
        cout <<  "Doesn't form cycle!" << endl;
        relate(&d,&f);
    }

    //Cycle
    if (formsCycle(&c,&b)){
        cout <<  "Forms cycle!" << endl;
    } else {
        cout <<  "Doesn't form cycle!" << endl;
        relate(&c,&b);
    }

    b.predecessors.append(&c);
    c.successors.append(&b);

    string tree = drawTree(&c).toUtf8().constData();
    cout << tree << endl;

    string graph = drawGraph(&c).toUtf8().constData();
    cout << graph << endl;
    cout << "OK" << endl;
    return 0;
    //      END OF TEST AREA




    //return a.exec();
}
