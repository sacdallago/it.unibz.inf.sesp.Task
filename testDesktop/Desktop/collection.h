#ifndef COLLECTION_H
#define COLLECTION_H

#include <QList>
#include "task.h"
#include "taskutilities.h"

class Collection {
private:
    QList<Task*> roots;
    QList<Task*> leaves;
    QList<Task*> all;
    bool rootsUpToDate;
    bool leavesUpToDate;
    qint64 maxTime;
    void calculateMaxTime();
public:
    Collection();
    void addItem(Task *);
    void removeItem(Task *);
    void emptyCollection();
    Task* get(qint64);
    bool relate(qint64,qint64);
    QList<Task*>* getRoots();
    QList<Task*>* getLeaves();
    QList<Task*> getTodoList();
    const QList<Task*>* getAll();
    QString printForest();
};

#endif // COLLECTION_H
