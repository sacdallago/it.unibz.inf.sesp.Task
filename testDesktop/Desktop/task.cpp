#include "task.h"
#include "utilities.h"
#include <iostream>

using namespace std;
//CONSTRUCTOR
Task::Task(qint64 id, qint64 importance, qint64 durationInH, QString name, QString description, qint64 status, qint64 relatives){
    this->id = id;
    this->importance = importance;
    this->durationInH = durationInH;
    this->name = name;
    this->description = description;
    this->status = status;
    this->relatives = relatives;
    time = getCurrentTime();
}

//METHODS

void Task::addSuccessor(Task * t){
    successors.append(t);
}
void Task::addPredecessor(Task * t){
    predecessors.append(t);
}
void Task::removeSuccessor(Task * t){
    successors.removeOne(t);
}
void Task::removePredecessor(Task * t){
    successors.removeOne(t);
}

QString Task::taskSuccessors(qint64 level){
    QString result = "";
    result+= QString::fromStdString(std::string( level, '\t' ));
    result+= QString::number(id) + " - " + name;
    result+= "\n";
    for(Task *t : successors){
        result += t->taskSuccessors(level+1);
    }
    return result;
}

QString Task::taskPredecessors(qint64 *depth, qint64 level){
    QString result = "";
    if(predecessors.empty()){
        if(*depth < level){
           *depth = level;
        }
    } else {
        for(Task *t : predecessors){
            result = t->taskPredecessors(depth ,level+1) + result;
        }
    }
    result+= QString::fromStdString(std::string(*depth-level, '\t' ));
    result+= QString::number(id) + " - " + name;
    result+= "\n";
    return result;
}

QString Task::drawTree(qint64 level){
    qint64 i=0;
    QString result = "";
    if(predecessors.empty()){
        if(i < level){
           i = level;
        }
    } else {
        for(Task *t : predecessors){
            result = t->taskPredecessors(&i ,level+1) + result;
        }
    }
    result+= QString::fromStdString(std::string(i-level, '\t' ));
    result+= QString::number(id) + " - " + name;
    result+= "\n";

    for(Task *t : successors){
        result += t->taskSuccessors(i+1);
    }
    return result;
}

qint64 Task::graph(Task* caller, QList<edge> *edges, QList<Task*> *discovered, qint64 *depth, qint64 *height, qint64 level){
    discovered->append(this);
    if(predecessors.empty()){
        if(*depth > level){
           *depth = level;
        }
    } else {
        for(Task *t : predecessors){
            if(!discovered->contains(t)){
                t->graph(this, edges , discovered, depth,height ,level-1);
            }
        }
    }
    if(successors.empty()){
        if(*height < level){
           *height = level;
        }
    } else {
        for(Task *t : successors){
            if(!discovered->contains(t)){
                t->graph(this, edges, discovered, depth,height, level+1);
            }
        }
    }
    edge e;
    e.from = caller;
    e.to = this;
    e.level = level;
    edges->append(e);
    return 1 - *depth;
}

QString Task::drawGraph(qint64 level){
    QList<edge> edges;
    QList<Task*> discovered;
    qint64 depth = 1;
    qint64 height = -1;
    qint64 offset = graph(this,&edges, &discovered, &depth, &height, level);
    QString s = "\n";
    s+="Nodes are ordered based on hight (first nodes (roots) are represented on the left\n";
    s+="and are at height " + QString::number(height+offset) + ").\n";
    s+="The first number represents the node's ID and the numbers in parenthesis the child\n";
    s+="nodes ID's. So, for example, 1E(2, 3) means 1 is father of 2 and 3.\n";
    QMap<qint64, QList<Task*> > treeGraph;
    for(edge e : edges){
        treeGraph[e.level + offset].append(e.to);
    }
    for(qint64 k : treeGraph.keys()){
        for(Task* t : treeGraph[k]){
            s+= QString::fromStdString(std::string(height+offset-k, '\t' )) +QString::number(t->getId());
            if(!t->predecessors.empty()){
                s+= "E(";
                QString p = "";
                for(Task* t1 : t->predecessors){
                    p+= QString::number(t1->getId()) + ", ";
                }
                s+=p.left(p.size()-2) + ")";
            }

            s+= "\n";
        }
    }
    return s;
}

QString Task::printTask(){
    QString result = "";
    result += "Task ID: " + QString::number(id) + "\n";
    result += "Task Name: " + name + "\n";
    result += "Task Description: " + description + "\n";
    result += "Task Importance: " + QString::number(importance) + "\n";
    result += "Task Duration (h): " + QString::number(durationInH) + "\n";
    result += "Child(1) or Root(0): " + QString::number(relatives) + "\n";
    result += "Done(-1), todo(0) or active(1): " + QString::number(status) + "\n";
    result += "Creation on: " + time + "\n";
    return result;
}

//INTERESTING GETTERS
QList<Task *>* Task::getPredecessors() {
    return &predecessors;
}
QList<Task *>* Task::getSuccessors(){
    return &successors;
}
//GETTERS & SETTERS
qint64 Task::getId() const {
    return id;
}
void Task::setId(const qint64 &value) {
    id = value;
}
qint64 Task::getImportance() const {
    return importance;
}
void Task::setImportance(const qint64 &value) {
    importance = value;
}
qint64 Task::getDurationInH() const {
    return durationInH;
}
void Task::setDurationInH(const qint64 &value) {
    durationInH = value;
}
QString Task::getName() const {
    return name;
}
void Task::setName(const QString &value) {
    name = value;
}
QString Task::getDescription() const {
    return description;
}
void Task::setDescription(const QString &value) {
    description = value;
}
QString Task::getTime() const {
    return time;
}
void Task::setTimeToCurrentTime() {
    time = getTime();
}
qint64 Task::getStatus() const {
    return status;
}
void Task::setStatus(const qint64 &value) {
    status = value;
}
qint64 Task::getRelatives() const {
    return relatives;
}
void Task::setRelatives(const qint64 &value) {
    relatives = value;
}
