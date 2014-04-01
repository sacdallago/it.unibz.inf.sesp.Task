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
        predecessor->addPredecessor(successor);
        successor->addSuccessor(predecessor);
        return true;
    }
}
