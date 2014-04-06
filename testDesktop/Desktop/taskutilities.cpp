#include "taskutilities.h"

bool TaskUtilities::relate(Task *predecessor, Task *successor){
    QList<Task*> linearGraph;
    QList<Task::edge> smt;
    qint64 depth = 0;
    qint64 height = 0;
    predecessor->graph(predecessor,&smt,&linearGraph, &depth,&height, 0);
    if(linearGraph.contains(successor)){
        return false;
    } else {
        predecessor->addSuccessor(successor);
        successor->addPredecessor(predecessor);
        return true;
    }
}

QString TaskUtilities::printList(QList<Task*> *list){
    QString result = "";
    for(Task *t : *list){
        result.append(t->printTask());
    }
    return result;
}
