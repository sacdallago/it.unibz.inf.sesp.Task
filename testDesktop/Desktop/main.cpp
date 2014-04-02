#include "widget.h"
#include "task.h"
#include "collection.h"
#include "connection.h"
#include "taskutilities.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[]) {
    //QApplication a(argc, argv);
    //Widget w;
    //w.show();

    //      DATABASE TEST AREA
    Connection connection;

    if(connection.close()){
        cout << "The connection has been closed, id est, it was opened before! :) A good sign!" <<endl;
    }

    //      TASK TEST AREA
    using namespace std;
    Collection col;
    col.addItem(new Task(1,1,1,"a"));
    col.addItem(new Task(2,1,1,"b"));
    col.addItem(new Task(3,1,1,"c"));
    col.addItem(new Task(4,1,1,"d"));
    col.addItem(new Task(5,1,1,"e"));
    col.addItem(new Task(6,1,1,"f"));
    col.addItem(new Task(7,1,1,"g"));

    //Dependencies get loaded from DATABASE
    if (TaskUtilities::relate(col.get(1),col.get(2))){
        cout <<  "Doesn't form cycle!" << endl;
    } else {
        cout <<  "Forms cycle!" << endl;
    }
    if (TaskUtilities::relate(col.get(1),col.get(3))){
            cout <<  "Doesn't form cycle!" << endl;
        } else {
            cout <<  "Forms cycle!" << endl;
        }
    if (TaskUtilities::relate(col.get(3),col.get(5))){
        cout <<  "Doesn't form cycle!" << endl;
    } else {
        cout <<  "Forms cycle!" << endl;
    }
    if (TaskUtilities::relate(col.get(3),col.get(6))){
        cout <<  "Doesn't form cycle!" << endl;
    } else {
        cout <<  "Forms cycle!" << endl;
    }
    if (TaskUtilities::relate(col.get(4),col.get(6))){
        cout <<  "Doesn't form cycle!" << endl;
    } else {
        cout <<  "Forms cycle!" << endl;
    }

    //Cycle
    if (TaskUtilities::relate(col.get(3),col.get(2))){
        cout <<  "Doesn't form cycle!" << endl;
    } else {
        cout <<  "Forms cycle!" << endl;
    }

    string tree = (*col.get(1)).drawGraph().toUtf8().constData();
    cout << tree << endl;

    return 0;
    //      END OF TEST AREA

    //return a.exec();
}
