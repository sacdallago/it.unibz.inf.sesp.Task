#include "collection.h"

Collection::Collection() {
    upToDate = true;
}

void Collection::addItem(Task *t){
    all.append(t);
    upToDate = false;
}

void Collection::removeItem(Task *t){
    QList<Task*> *su= t->getSuccessors();
    QList<Task*> *pre= t->getPredecessors();
    for(Task *s: *su){
        s->getPredecessors()->removeOne(t);
    }
    for(Task *p: *pre){
        p->getSuccessors()->removeOne(t);
    }
    //REMOVE FROM DATABASE!!
    all.removeOne(t);
    upToDate = false;
}

void Collection::emptyCollection(){
    all.clear();
    roots.clear();
    leafs.clear();
    upToDate = true;
}

Task* Collection::get(qint64 id){
    for(Task *t : all){
        if(t->getId() == id){
            return t;
        }
    }
    return NULL;
}

QList<Task*>* Collection::getRoots(){

}

QList<Task*>* Collection::getLeafs(){

}

const QList<Task*>* Collection::getAll(){

}
