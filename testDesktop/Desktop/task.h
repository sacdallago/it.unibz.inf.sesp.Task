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
        FATHER = 0,
        CHILDREN = 1,
        BOTH = 2
    };
}

//Task Definition
struct Task{
    unsigned long long id = 0;
    int importance = 0;
    int durationInH = 0;
    double rank = 0.0;
    string Name = "DEFAULT";
    int status = Status::TODO;
    int relatives = Relatives::FATHER;
    QList<Task> successors;
};

typedef struct Task Task;

#endif // TASK_H
