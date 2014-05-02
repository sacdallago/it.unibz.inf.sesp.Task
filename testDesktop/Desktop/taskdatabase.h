#ifndef TASKDATABASE_H
#define TASKDATABASE_H

#include "task.h"
#include "connection.h"

class TaskDatabase : public Connection{
private:
    qint64 userID;
    QString username;
public:
    TaskDatabase(QString driver = "QPSQL", QString server = "ufficio.zucchitours.com", QString db = "sesp_task_test", QString username = "sesp_tasker", QString password = "7m6wvT&0");

    bool login(QString taskUser, QString taskPassword);
    bool createUser(QString taskUser, QString taskPassword);
    bool deleteUser(QString taskUser);
    void logout();

    Task* getTask(qint64 id);
    Task* insertTask(QString name, qint64 importance, qint64 duration, QString description, qint64 status);
    bool signalDone(qint64 task);
    bool insertTask(Task *);
    bool removeTask(Task *);
    bool deleteRelation(qint64 father, qint64 child);
    bool insertRelation(qint64 father, qint64 child);
    bool insertRelations(Task *father);
    bool insertRelations(QList<Task*> *fathers, QList<Task*> *children);
    bool update(Task *modified);
    bool clear();
};

#endif // TASKDATABASE_H
