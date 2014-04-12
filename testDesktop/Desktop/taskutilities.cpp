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

void TaskUtilities::tasksFromQuery(Collection *c, const QMap<QString, QList<QVariant> *> *query){
    qint64 elements = query->first()->size();
    for(qint64 i=0;i<elements;i++){
        qint64 id = query->value("id")->value(i).toInt();
        qint64 importance = query->value("importance")->value(i).toInt();
        qint64 durationInH = query->value("duration")->value(i).toInt();
        QString name = query->value("name")->value(i).toString();
        QString description = query->value("description")->value(i).toString();
        QString time = query->value("creation")->value(i).toString();
        qint64 status = query->value("status")->value(i).toInt();
        Task *t = new Task(id,importance,durationInH,name,description,status);
        t->setTime(time);
        c->addItem(t);
    }
}

void TaskUtilities::relateFromQuery(Collection *c, const QMap<QString, QList<QVariant> *> *query){
    qint64 elements = query->first()->size();
    for(qint64 i=0;i<elements;i++){
        c->relate(query->value("father")->value(i).toInt(),query->value("child")->value(i).toInt());
    }
}
