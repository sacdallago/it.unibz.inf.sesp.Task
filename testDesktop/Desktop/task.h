#ifndef TASK_H
#define TASK_H

#include <QList>

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
struct Task{
    unsigned long long id = 0;
    int importance = 0;
    int durationInH = 0;
    string Name = "DEFAULT";
    int status = Status::TODO;
    int relatives = Relatives::ROOT;
    QList<Task> successors;
    QList<Task> predecessors;
};

typedef struct Task Task;

#endif // TASK_H
