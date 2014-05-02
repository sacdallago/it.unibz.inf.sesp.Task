#ifndef COLLECTION_H
#define COLLECTION_H

#include <QList>
#include "task.h"
#include "taskdatabase.h"

class Collection {
private:
    QList<Task*> all;
    QList<Task*> doneTasks;
    qint64 maxTime;
    void calculateMaxTime();
    TaskDatabase *connection;
public:
    Collection(TaskDatabase * c = new TaskDatabase());

    //Operational -- insertions and deletions of new tasks + optional update reflection on DB.
    /*!
     * \brief addItem using a pointer to an existing task type. Doesn't interact with database
     * \param updateDB
     */
    void addItem(Task *);
    /*!
     * \brief addItem using the database to assign the id, a new task is created and added to the db. This task is then added to the collection using the insertItem(Task*) method.
     * \param name name of the task
     * \param importance importance on a scale from 0 to 10 (inclusive)
     * \param duration estimated duration for the task coalculated in hours
     * \param description description for the task
     * \param status status, either done (1) or todo (0)
     * \return returns true if task was added.
     */
    Task* addItem(QString name, qint64 importance, qint64 duration, QString description, qint64 status);
    /*!
     * \brief removeItem removes one Task
     * \param updateDB. Set to true by default. If set to false, will not reflect changes on DB.
     * \return
     */
    bool removeItem(Task *, bool updateDB = true);
    /*!
     * \brief removeItem removes one Task
     * \param updateDB. Set to true by default. If set to false, will not reflect changes on DB.
     * \return
     */
    bool removeItem(qint64, bool updateDB = true);
    /*!
     * \brief emptyCollection empties the collection.
     * \param updateDB set to true by default. If set to false doesn't reflect changes on DB.
     */
    void emptyCollection(bool updateDB = true);
    /*!
     * \brief relate relates two tasks where the father is the first argument and the child the second.
     * \param father
     * \param child
     * \param updateDB set to true by default. If set to false doesn't reflect changes on DB.
     * \return
     */
    bool relate(qint64 father,qint64 child, bool updateDB = true);
    /*!
     * \brief relate relates two tasks where the father is the first argument and the child the second.
     * \param father
     * \param child
     * \param updateDB set to true by default. If set to false doesn't reflect changes on DB.
     * \return
     */
    bool relate(Task* father,Task* child, bool updateDB = true);
    /*!
     * \brief unrelate unrelates two tasks where the father is the first argument and the child the second.
     * \param father
     * \param child
     * \param updateDB set to true by default. If set to false doesn't reflect changes on DB.
     * \return
     */
    bool unrelate(qint64 father ,qint64 child, bool updateDB = true);
    /*!
     * \brief unrelate unrelates two tasks where the father is the first argument and the child the second.
     * \param father
     * \param child
     * \param updateDB set to true by default. If set to false doesn't reflect changes on DB.
     * \return
     */
    bool unrelate(Task* father ,Task* child, bool updateDB = true);


    //Update happens transperently (you just modify the attributes of a task with a setter)!
    /*!
     * \brief If you want to update a task, you call it's setter methods. This method serves
     * to make modifictions permament (rewrite the update task to database).
     * \return returns true if database was successfully updated
     */
    bool update(Task *);

    /*!
     * \brief done Signals that a task has been done. Will take care of removing all relations and setting it's status to done!
     * \param d The task that has been done
     */
    void done(Task * d);

    bool login(QString taskUser, QString taskPassword);

    void logout();

    void populateFromDatabase();

    // Retrieval
    Task* get(qint64);
    QList<Task*>* getRoots();
    QList<Task*>* getLeaves();
    QList<Task*> getDoneList();
    QList<Task*> getTodoList();
    const QList<Task*>* getAll();
    QString printForest();
    TaskDatabase *getConnection();
};

#endif // COLLECTION_H
