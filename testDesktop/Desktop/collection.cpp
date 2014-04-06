#include "collection.h"

Collection::Collection() {
    rootsUpToDate = true;
    leavesUpToDate = true;
    maxDependency = 0;
    maxTime = 0;
}

void Collection::addItem(Task *t){
    all.append(t);
    if(t->getDurationInH() > maxTime){
        maxTime = t->getDurationInH();
    }
    rootsUpToDate = false;
    leavesUpToDate = false;
}

//Performance = k = O(n)
void Collection::calculateMaxTime(){
    for(Task *t : all){
        if(t->getDurationInH() > maxTime){
            maxTime = t->getDurationInH();
        }
    }
}

void Collection::removeItem(Task *t){
    QList<Task*> *su= t->getSuccessors();
    QList<Task*> *pre= t->getPredecessors();
    for(Task *s: *su){
        //REMOVE FROM DATABASE!!
        s->getPredecessors()->removeOne(t);
    }
    for(Task *p: *pre){
        //REMOVE FROM DATABASE!!
        p->getSuccessors()->removeOne(t);
    }
    //REMOVE FROM DATABASE!!
    all.removeOne(t);
    if(t->getDurationInH() == maxTime){
        calculateMaxTime();
    }
    rootsUpToDate = false;
    leavesUpToDate = false;
}

void Collection::emptyCollection(){
    all.clear();
    roots.clear();
    leaves.clear();
    rootsUpToDate = true;
    leavesUpToDate = true;
}

Task* Collection::get(qint64 id){
    for(Task *t : all){
        if(t->getId() == id){
            return t;
        }
    }
    return NULL;
}

bool Collection::relate(qint64 predecessor,qint64 successor){
    Task* pre = get(predecessor);
    Task* suc = get(successor);
    if(pre != NULL && suc != NULL){
        if(TaskUtilities::relate(pre,suc)){
            rootsUpToDate = false;
            leavesUpToDate = false;
            return true;
        }
        return false;
    } else {
        return false;
    }
}

void upwalk(Task *t, QList<Task*> *visited, QList<Task*> *roots){
    if(!visited->contains(t)){
        visited->append(t);
        if(t->getPredecessors()->empty()){
            roots->append(t);
        } else {
            QList<Task*> *pre= t->getPredecessors();
            for(Task *p : *pre){
                upwalk(p, visited, roots);
            }
        }
    }
}

QList<Task*>* Collection::getRoots(){
    if(!rootsUpToDate){
        roots.clear();
        QList<Task*> visited;
        for(Task* t : all){
            upwalk(t,&visited,&roots);
        }
    }
    rootsUpToDate = true;
    return &roots;
}

void downwalk(Task *t, QList<Task*> *visited, QList<Task*> *leaves){
    if(!visited->contains(t)){
        visited->append(t);
        if(t->getSuccessors()->empty()){
            leaves->append(t);
        } else {
            QList<Task*> *suc= t->getSuccessors();
            for(Task *s : *suc){
                downwalk(s, visited, leaves);
            }
        }
    }
}

QList<Task*>* Collection::getLeaves(){
    if(!leavesUpToDate){
        leaves.clear();
        QList<Task*> visited;
        for(Task* t : all){
            downwalk(t,&visited,&leaves);
        }
    }
    leavesUpToDate = true;
    return &leaves;
}

const QList<Task*>* Collection::getAll(){
    return &all;
}

QString Collection::printForest(){
    QString result = "";
    QList<Task*> visited;
    for(Task *t : all){
        if(!visited.contains(t)){
            result += t->drawGraph(&visited);
        }
    }
    return result;
}
