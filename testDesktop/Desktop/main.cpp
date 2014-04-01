#include "widget.h"
#include "task.h"
#include "taskutilities.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[]) {
    //QApplication a(argc, argv);
    //Widget w;
    //w.show();

    //      TEST AREA
    using namespace std;
    Task a = Task(1,1,1,"a"), b = Task(2,1,1,"b"), c = Task(3,1,1,"c"), d = Task(4,1,1,"d"), e = Task(5,1,1,"e") ,f = Task(6,1,1,"f");

    //Dependencies get loaded from DATABASE
    if (TaskUtilities::relate(&a,&b)){
        cout <<  "Doesn't form cycle!" << endl;
    } else {
        cout <<  "Forms cycle!" << endl;
    }
    if (TaskUtilities::relate(&a,&c)){
            cout <<  "Doesn't form cycle!" << endl;
        } else {
            cout <<  "Forms cycle!" << endl;
        }
    if (TaskUtilities::relate(&c,&e)){
        cout <<  "Doesn't form cycle!" << endl;
    } else {
        cout <<  "Forms cycle!" << endl;
    }
    if (TaskUtilities::relate(&c,&f)){
        cout <<  "Doesn't form cycle!" << endl;
    } else {
        cout <<  "Forms cycle!" << endl;
    }
    if (TaskUtilities::relate(&d,&f)){
        cout <<  "Doesn't form cycle!" << endl;
    } else {
        cout <<  "Forms cycle!" << endl;
    }

    //Cycle
    if (TaskUtilities::relate(&c,&b)){
        cout <<  "Doesn't form cycle!" << endl;
    } else {
        cout <<  "Forms cycle!" << endl;
    }

    string tree = a.drawGraph().toUtf8().constData();
    cout << tree << endl;
    cout << "OK" << endl;
    return 0;
    //      END OF TEST AREA

    //return a.exec();
}
