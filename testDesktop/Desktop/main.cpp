#include "widget.h"
#include "collection.h"
#include "connection.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[]) {
    //QApplication a(argc, argv);
    //Widget w;
    //w.show();

    //      DATABASE TEST AREA
    //Connection connection;

    //if(connection.close()){
    //    cout << "The connection has been closed, id est, it was opened before! :) A good sign!" <<endl;
    //}

    //      TASK TEST AREA
    using namespace std;
    Collection col;
    col.addItem(new Task(14,6,5,"14"));
    col.addItem(new Task(15,3,6,"15"));
    col.addItem(new Task(109,8,2,"109"));
    col.addItem(new Task(54,4,6,"54"));
    col.addItem(new Task(34,3,1,"34"));
    col.addItem(new Task(63,9,8,"63"));
    col.addItem(new Task(6,1,2,"6"));
    col.addItem(new Task(35,6,2,"35"));
    col.addItem(new Task(99,9,1,"99"));
    col.addItem(new Task(69,3,4,"69"));

    col.relate(15,109);
    col.relate(15,63);
    col.relate(63,6);
    col.relate(69,6);
    col.relate(54,34);

    string s = col.printForest().toUtf8().constData();
    cout << "Forest:\n" << s << endl;

    col.getTodoList();
    //      END OF TEST AREA

    //return a.exec();
}
