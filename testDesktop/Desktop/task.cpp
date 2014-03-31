#include "task.h"
#include <QString>
#include <ctime>
#include <iostream>

QString printTask(Task *a){
    QString result = "";
    result += "Task ID: " + QString::number(a->id) + "\n";
    result += "Task Name: " + a->name + "\n";
    result += "Task Description: " + a->description + "\n";
    result += "Task Importance: " + QString::number(a->importance) + "\n";
    result += "Task Duration (h): " + QString::number(a->durationInH) + "\n";
    result += "Child(1) or Root(0): " + QString::number(a->relatives) + "\n";
    result += "Done(-1), todo(0) or active(1): " + QString::number(a->status) + "\n";
    result += "Creation on: " + a->time + "\n";
    return result;
}

QString getTime(){
    char out[15];
    std::time_t t=std::time(NULL);
    std::strftime(out, sizeof(out), "%Y%m%d%H%M%S", std::localtime(&t));
    QString str(out);
    return str;
}


QString taskSuccessors(Task *start, size_t level){
    QString left = "";
    left+= QString::fromStdString(std::string( level, '\t' ));
    left+= QString::number(start->id) + " - " + start->name;
    left+= "\n";
    for(Task *t : start->successors){
        left += taskSuccessors(t,level+1);
    }
    return left;
}

QString taskPredecessors(Task *child, size_t *depth, size_t level){
    QString result = "";
    if(child->predecessors.empty()){
        if(*depth < level){
           *depth = level;
        }
    } else {
        for(Task *t : child->predecessors){
            result = taskPredecessors(t,depth ,level+1) + result;
        }
    }
    result+= QString::fromStdString(std::string(*depth-level, '\t' ));
    result+= QString::number(child->id) + " - " + child->name;
    result+= "\n";
    return result;
}

QString drawTree(Task* start, size_t level){
    size_t i=0;
    QString result = "";
    if(start->predecessors.empty()){
        if(i < level){
           i = level;
        }
    } else {
        for(Task *t : start->predecessors){
            result = taskPredecessors(t,&i ,level+1) + result;
        }
    }
    result+= QString::fromStdString(std::string(i-level, '\t' ));
    result+= QString::number(start->id) + " - " + start->name;
    result+= "\n";

    for(Task *t : start->successors){
        result += taskSuccessors(t,i+1);
    }
    return result;
}


/*
 * ATTENZIONE!!! SIZE_T E' UNSIGNED!!!! TROVARE VERSIONE SIGNED ED DISEGNARE ALBERO IN BASE AD UNA NUOVA STRUCT
 * struct node{
 *      Task* t;
 *      signed size_t level;
 * }
 */

struct node{
     Task* t;
     size_t level;
 };


QString graph(Task *start,QList<Task*> *discovered, size_t *depth, size_t level){
    QString result = "";
    discovered->append(start);
    if(start->predecessors.empty()){
        if(*depth < level){
           *depth = level;
        }
    } else {
        for(Task *t : start->predecessors){
            if(!discovered->contains(t)){
                result += graph(t,discovered, depth ,level+1);
            }
        }
    }
    for(Task *t : start->successors){
        if(!discovered->contains(t)){
            result += graph(t,discovered, depth,level-1);
        }
    }
    result+= QString::fromStdString(std::string(0, '\t' ));
    result+= QString::number(level) + ", ID: "+ QString::number(start->id) + ", Name: " + start->name;
    result+= "\n";
    //cout << result.toStdString() <<endl;
    return result;
}

QString drawGraph(Task *start, size_t level){
    QList<Task*> discovered;
    size_t depth = 0;
    QString s = graph(start, &discovered, &depth, level);
    //cout << depth << endl;
    return s;
}

bool formsCycle(Task *addition, Task *target){
    QList<Task*> discovered;
    size_t depth = 0;
    graph(target, &discovered, &depth, 0);
    if (discovered.contains(addition)){
        return true;
    } else {
        return false;
    }
}

bool relate(Task *predecessor, Task *successor){
    predecessor->successors.append(successor);
    successor->predecessors.append(predecessor);
    return true;
}
