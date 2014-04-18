#include "collection.h"
#include "taskutilities.h"

Collection::Collection(Connection *c) {
    rootsUpToDate = true;
    leavesUpToDate = true;
    connection = c;
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

Task* Collection::addItem(QString name, qint64 importance, qint64 duration, QString description, qint64 status){
    Task *toBeAdded = connection->insertTask(name,importance,duration,description,status);
    if(toBeAdded != NULL){
        addItem(toBeAdded);
    }
    return toBeAdded;
}

//Performance = k = O(n)
void Collection::calculateMaxTime(){
    for(Task *t : all){
        if(t->getDurationInH() > maxTime){
            maxTime = t->getDurationInH();
        }
    }
}

Connection *Collection::getConnection(){
    return connection;
}

bool Collection::removeItem(Task *t){
    if(t != NULL && connection->removeTask(t)){
        QList<Task*> *su= t->getSuccessors();
        QList<Task*> *pre= t->getPredecessors();
        for(Task *s: *su){
            //Every successor will be a child of every predecessor
            for(Task *p: *pre){
                p->getSuccessors()->removeOne(t);
            }
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
        return true;
    } else {
        return false;
    }
}

bool Collection::update(Task * t){

}

bool Collection::removeItem(qint64 id){
    return removeItem(get(id));
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
            connection->insertRelation(predecessor,successor);
            return true;
        }
        return false;
    } else {
        return false;
    }
}

bool Collection::unrelate(qint64 predecessor,qint64 successor){
    Task* pre = get(predecessor);
    Task* suc = get(successor);
    if(pre != NULL && suc != NULL){
        if(pre->getSuccessors()->contains(suc)){
            rootsUpToDate = false;
            leavesUpToDate = false;
            connection->deleteRelation(predecessor,successor);
            pre->getSuccessors()->removeOne(suc);
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

//O(nlogn) This could be donw at the insertion phase!!!!!!!!!!! To speed up at least this part. It would slow down retriefal SLIGHTLY but it's worth a shot!
void todoListAccessory(Task *t, QHash<Task*,qint64> *map, qint64 level, qint64 *maxLevel){
    if(*maxLevel < level){
        *maxLevel = level;
    }
    if(map->contains(t)){
        if(map->value(t) < level){
            map->insert(t,level);
        }
    } else {
        map->insert(t, level);
    }
    for(Task *pre : *t->getPredecessors()){
        //cout << pre->getId() << " ";
        todoListAccessory(pre, map, level+1, maxLevel);
    }
}

//VERY BAD!!! O(n4)
QList<Task*> Collection::getTodoList(){
    QList<Task*> list;
    qint64 maxDependency = 0;
    QList<Task*>* leaves = getLeaves();
    QHash<Task*, qint64> hash;
    QMap<qreal, Task*> map;

    for(Task *leaf : *leaves){
        todoListAccessory(leaf,&hash, 1, &maxDependency);
    }

    cout << "max(duration):\t" << maxTime << "\tduration quantum:\t" << 10.0/maxTime << endl;
    cout << "max(dependency):\t" << maxDependency << "\tdependency quantum:\t" << 10.0/maxDependency << endl << endl;

    foreach (Task *key, hash.keys()){
        qreal rank = ((key->getImportance()/2.0)-((key->getDurationInH()*(10.0/maxTime))/2.0)+5)*(5.0/6.0)+(hash.value(key)*10.0/maxDependency)*(1.0/6.0);
        if(map.contains(-rank)){
            cout << "Duplicate!!!!" << endl;
        }
        map.insert(-rank,key);
    }

    QMap<qreal, Task*>::iterator i;

    bool wantNext = false;
    while(!map.empty()){
        for(i = map.begin(); i != map.end() ; ++i){
            wantNext = false;
            cout << "Now looking at: " << map[i.key()]->getId() << "\n";
            foreach (Task *predecessor, *map[i.key()]->getPredecessors()){
                if(!list.contains(predecessor)){
                    cout << "\tList doesn't contain " << predecessor->getId() << endl;
                    wantNext = true;
                    break;
                }
            }
            if(!wantNext){
                cout << "----->All dependencies met, adding "<< map.value(i.key())->getId() << endl;
                list.append(map.value(i.key()));
                map.remove(i.key());
                break;
            }
        }
        cout << endl;
    }

    cout << "Order in which you should approach tasks:" << endl;
    foreach(Task *ordered, list){
        cout << "ID:\t" << ordered->getId() << endl;
    }

    return list;
}
