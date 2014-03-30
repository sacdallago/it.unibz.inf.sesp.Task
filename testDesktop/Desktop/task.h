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
};

typedef struct Task Task;

QString printTask(Task);

#endif // TASK_H
