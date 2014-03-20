#ifndef TASK_H
#define TASK_H

using namespace std;

//Task Definition

struct Task{
    unsigned long long id;
    int gradeOfDifficulty;
    int durationInH;
    double rank;
    string Name;
};

typedef struct Task Task;

#endif // TASK_H
