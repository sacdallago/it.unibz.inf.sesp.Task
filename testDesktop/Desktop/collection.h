#ifndef COLLECTION_H
#define COLLECTION_H

#include <QList>
#include "task.h"
#include "connection.h"

class Collection {
private:
    QList<Task*> roots;
    QList<Task*> leaves;
    QList<Task*> all;
    bool rootsUpToDate;
    bool leavesUpToDate;
    qint64 maxTime;
    void calculateMaxTime();
    Connection *connection;
public:
    Collection(Connection * c = new Connection());
    void addItem(Task *);
    Task* addItem(QString name, qint64 importance, qint64 duration, QString description, qint64 status);
    bool removeItem(Task *);
    bool removeItem(qint64);
    bool update(Task *);
    void emptyCollection();
    Task* get(qint64);
    bool relate(qint64,qint64);
    bool unrelate(qint64,qint64);
    QList<Task*>* getRoots();
    QList<Task*>* getLeaves();
    QList<Task*> getTodoList();
    const QList<Task*>* getAll();
    QString printForest();
    Connection *getConnection();
};

#endif // COLLECTION_H
