#ifndef COLLECTION_H
#define COLLECTION_H

#include <QList>
#include "task.h"

class Collection {
private:
    QList<Task*> roots;
    QList<Task*> leafs;
    QList<Task*> all;
    bool upToDate;
public:
    Collection();
    void addItem(Task *);
    void removeItem(Task *);
    void emptyCollection();
    Task* get(qint64);
    QList<Task*>* getRoots();
    QList<Task*>* getLeafs();
    const QList<Task*>* getAll();
};

#endif // COLLECTION_H
