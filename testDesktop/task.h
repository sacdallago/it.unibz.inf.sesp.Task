#ifndef TASK_H
#define TASK_H

#include <QList>

using namespace std;

//Status Definition
struct Status{
    int done = -1;
    int todo = 0;
    int active = 1;
};

typedef const struct Status Status;

//Task Definition
struct Task{
    unsigned long long id = 0;
    int importance = 0;
    int durationInH = 0;
    double rank = 0.0;
    string Name = "DEFAULT";
    Status status = Status.todo;
    QList<Task> predecessors;
    QList<Task> successors;
};

typedef struct Task Task;

#endif // TASK_H
