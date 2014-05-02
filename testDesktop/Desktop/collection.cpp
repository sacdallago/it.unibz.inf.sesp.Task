#include "collection.h"
#include "taskutilities.h"

Collection::Collection(TaskDatabase *c) {
    connection = c;
    maxTime = 0;
}

//Performance = k = O(n)
void Collection::calculateMaxTime(){
    for(Task *t : all){
        if(t->getDurationInH() > maxTime){
            maxTime = t->getDurationInH();
        }
    }
}

void Collection::addItem(Task *t){
    if(t->getStatus() != 0){
        doneTasks.append(t);
    } else {
        all.append(t);
    }
    if(t->getDurationInH() > maxTime){
        maxTime = t->getDurationInH();
    }
}

Task* Collection::addItem(QString name, qint64 importance, qint64 duration, QString description, qint64 status){
    Task *toBeAdded = toBeAdded = connection->insertTask(name,importance,duration,description,status);
    if(toBeAdded != NULL){
        addItem(toBeAdded);
    }
    return toBeAdded;
}

TaskDatabase *Collection::getConnection(){
    return connection;
}

bool Collection::removeItem(Task *t,bool updateDB){
    if(updateDB){
        if(t != NULL && connection->removeTask(t)){
            QList<Task*> *su= t->getSuccessors();
            QList<Task*> *pre= t->getPredecessors();
            for(Task *p: *pre){
                //Every successor will be a child of every predecessor
                for(Task *s: *su){
                    // NOT NEEDED! DATABASE CASCADES connection->deleteRelation(t->getId(),s->getId());
                    s->getPredecessors()->removeOne(t);
                    //relate(p,s);
                }
                // NOT NEEDED! DATABASE CASCADES connection->deleteRelation(p->getId(),t->getId());
                p->getSuccessors()->removeOne(t);
            }
            for(Task *p: *pre){
                for(Task *s: *su){
                    relate(p,s);
                }
            }
            all.removeOne(t);
            if(t->getDurationInH() == maxTime){
                calculateMaxTime();
            }
            return true;
        } else {
            return false;
        }
    } else {
        if(t != NULL){
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
                p->getSuccessors()->removeOne(t);
            }
            all.removeOne(t);
            if(t->getDurationInH() == maxTime){
                calculateMaxTime();
            }
            return true;
        } else {
            return false;
        }
    }
}

void Collection::done(Task * t){
    t->setStatus(1);
    update(t);
}

bool Collection::update(Task * t){
    return connection->update(t);
}

bool Collection::removeItem(qint64 id,bool updateDB){
    return removeItem(get(id), updateDB);
}

void Collection::emptyCollection(bool updateDB){
    all.clear();
    if(updateDB){
        connection->clear();
    }
}

Task* Collection::get(qint64 id){
    for(Task *t : all){
        if(t->getId() == id){
            return t;
        }
    }
    return NULL;
}

bool Collection::relate(Task* predecessor,Task* successor,bool updateDB){
    Task* pre = predecessor;
    Task* suc = successor;
    if(pre != NULL && suc != NULL){
        if(TaskUtilities::relate(pre,suc)){
            if(updateDB){
                connection->insertRelation(predecessor->getId(),successor->getId());
            }
            return true;
        }
        return false;
    } else {
        return false;
    }
}

bool Collection::relate(qint64 predecessor,qint64 successor,bool updateDB){
    Task* pre = get(predecessor);
    Task* suc = get(successor);
    if(pre != NULL && suc != NULL){
        if(TaskUtilities::relate(pre,suc)){
            if(updateDB){
                connection->insertRelation(predecessor,successor);
            }
            return true;
        }
        return false;
    } else {
        return false;
    }
}

bool Collection::unrelate(qint64 predecessor,qint64 successor, bool updateDB){
    Task* pre = get(predecessor);
    Task* suc = get(successor);
    if(pre != NULL && suc != NULL){
        if(pre->getSuccessors()->contains(suc)){
            if(updateDB){
                connection->deleteRelation(predecessor,successor);
            }
            pre->getSuccessors()->removeOne(suc);
            suc->getPredecessors()->removeOne(pre);
            return true;
        }
        return false;
    } else {
        return false;
    }
}

bool Collection::unrelate(Task* predecessor,Task* successor, bool updateDB){
    Task* pre = predecessor;
    Task* suc = successor;
    if(pre != NULL && suc != NULL){
        if(pre->getSuccessors()->contains(suc)){
            if(updateDB){
                connection->deleteRelation(predecessor->getId(),successor->getId());
            }
            pre->getSuccessors()->removeOne(suc);
            suc->getPredecessors()->removeOne(pre);
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
    QList<Task*> * roots = new QList<Task*>();
    QList<Task*> visited;
    for(Task* t : all){
        upwalk(t,&visited,roots);
    }
    return roots;
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
    QList<Task*> * leaves = new QList<Task*>();
    QList<Task*> visited;
    for(Task* t : all){
        downwalk(t,&visited,leaves);
    }
    return leaves;
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

QList<Task*> Collection::getDoneList(){
    return doneTasks;
}

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

bool Collection::login(QString taskUser, QString taskPassword){
    return connection->login(taskUser,taskPassword);
}

void Collection::logout(){
    connection->logout();
}
