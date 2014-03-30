#ifndef TASK_H
#define TASK_H

#include <QList>
#include <QString>

using namespace std;

//Status Definition
namespace Status{
    enum {
        DONE = -1,
        TODO = 0,
        ACTIVE = 1
    };
}
 //Relation Definition
namespace Relatives{
    enum{
        ROOT = 0,
        CHILD = 1
    };
}

//Task Definition
QString getTime();

struct Task{
    unsigned long long id = 0;
    int importance = 0;
    int durationInH = 0;
    QString name = "DEFAULT";
    QString description = "NO DESCRITPION.";
    QString time = getTime();
    int status = Status::TODO;
    int relatives = Relatives::ROOT;
    QList<Task*> successors;
    QList<Task*> predecessors;

    int discovered = 0;
};
typedef struct Task Task;

QString taskSuccessors(Task*, size_t level=0);
QString taskPredecessors(Task*, size_t*, size_t level = 0);
QString drawGraph(Task* start, size_t level = 1);
QString drawTree(Task* start, size_t level = 0);
QString graph(Task *start,QList<Task*> *discovered, size_t *depth, size_t level);
bool relate(Task *predecessor, Task *successor);
bool formsCycle(Task *addition, Task *target);

QString printTask(Task*);
bool checkCycle(Task* target, Task* successor);

#endif // TASK_H
