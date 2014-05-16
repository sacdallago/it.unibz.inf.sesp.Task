#ifndef TASK_H
#define TASK_H

#include <QList>
#include <QString>
#include <iostream>
#include <QMap>
#include <QHash>
#include <QMapIterator>
#include <QHashIterator>

using namespace std;

namespace Status{
    enum {
        TODO = 0,
        DONE = 1
    };
}

class Task {

private:
    struct edge {
        Task * from;
        Task * to;
        qint64 level;
    };

    qint64 id;
    qint64 importance;
    qint64 durationInH;
    QString name;
    QString description;
    QString time;
    qint64 status;
    QList<Task*> successors;
    QList<Task*> predecessors;
public:
    /*!
     * \brief Task class, containing a task.
     * \param id, the id (usually assigned by db, a counter
     * \param importance, the importance from 0 to 10
     * \param durationInH, the duration of the task expressed in hours.
     * \param name, the name of the task. Like "Pickup Milk"
     * \param description, the description. Like "Need the milk for the cake!"
     * \param status, status. Loaded from db, states weather it is done, to be done or active.
     * \param relatives, states if the task is a root or a child (no difference between leaf or inner child).
     */
    Task(qint64 id = 0, qint64 importance = 0, qint64 durationInH = 0, QString name = "DEFAULT", QString description = "NO DESCRITPION.", qint64 status = Status::TODO);
    Task(qint64 id, qint64 importance, qint64, QString name, QString description, qint64 status, QString creation);

    void addSuccessor(Task *);
    void addPredecessor(Task *);
    void removeSuccessor(Task *);
    void removePredecessor(Task *);

    QString taskSuccessors(qint64 level=0);
    QString taskPredecessors(qint64 *, qint64 level = 0);
    QString drawTree(qint64 level = 0);

    typedef struct edge edge;

    qint64 graph(Task* caller, QList<edge> *edges, QList<Task*> *discovered, qint64 *depth, qint64 *height, qint64 level);
    QString drawGraph(qint64 level = 1);
    QString drawGraph(QList<Task*>*, qint64 level = 1,  bool printInstructions = false);

    QString printTask();

    QList<Task *>* getPredecessors();
    QList<Task *>* getSuccessors();

    qint64 getId() const;
    void setId(const qint64 &value);
    qint64 getImportance() const;
    void setImportance(const qint64 &value);
    qint64 getDurationInH() const;
    void setDurationInH(const qint64 &value);
    QString getName() const;
    void setName(const QString &value);
    QString getDescription() const;
    void setDescription(const QString &value);
    QString getTime() const;
    void setTimeToCurrentTime();
    void setTime(const QString &value);
    qint64 getStatus() const;
    void setStatus(const qint64 &value);
};

#endif // TASK_H
