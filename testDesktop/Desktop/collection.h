#ifndef COLLECTION_H
#define COLLECTION_H

#include <QList>
#include "task.h"
#include "taskdatabase.h"

class Collection {
private:
    /*!
     * \brief all holds todo tasks, randomly
     */
    QList<Task*> all;
    /*!
     * \brief doneTasks holds all done tasks, randomly
     */
    QList<Task*> doneTasks;
    /*!
     * \brief maxTime indicates the maximum time of all todo tasks
     */
    qint64 maxTime;
    /*!
     * \brief calculateMaxTime recalculates maxTime
     */
    void calculateMaxTime();
    /*!
     * \brief connection holds the connection to the database where tasks are stored
     */
    TaskDatabase *connection;
public:
    /*!
     * \brief Collection Creates a bag where tasks can be put in or created and manages the time-scheduling operations
     * \param connection a connection to a database holding tasks
     */
    Collection(TaskDatabase * connection = new TaskDatabase());

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

    /*!
     * \brief login maps login function from database
     * \param taskUser username for the task user
     * \param taskPassword password for the task user
     * \return
     */
    bool login(QString taskUser, QString taskPassword);

    /*!
     * \brief cleans the class
     */
    void logout();

    /*!
     * \brief populateFromDatabase if the login has been done, this method populates the collection from the database, with the given user.
     */
    void populateFromDatabase();

    // Retrieval
    /*!
     * \brief get a task from the bag
     * \return retuns a pointer to a task in the bag, if there is any meeting the given id
     */
    Task* get(qint64);
    /*!
     * \brief getRoots returns a list of all those tasks that have no precedessors
     * \return a pointer to a list of pointers to tasks
     */
    QList<Task*>* getRoots();
    /*!
     * \brief getLeaves returns a list of all those tasks that have predecessors but no successors
     * \return a pointer to a list of pointers to tasks
     */
    QList<Task*>* getLeaves();
    /*!
     * \brief getDoneList returns a randomly ordered list of done tasks
     * \return a list of pointers to tasks
     */
    QList<Task*> getDoneList();
    /*!
     * \brief getTodoList returns an ordered list of todo tasks, ordered in a FIFO fashion
     * \return a list of pointers to tasks
     */
    QList<Task*> getTodoList();
    /*!
     * \brief getAll returns unordered list of todo tasks
     * \return a list of pointers to tasks
     */
    const QList<Task*>* getAll();
    /*!
     * \brief printForest gives a graphical (textual) representation of the todo tasks graph
     * \return returns a qstring representing such graph
     */
    QString printForest();
    /*!
     * \brief getConnection
     * \return returns a pointer to the task database, to call methods on it directly.
     */
    TaskDatabase *getConnection();
    ~Collection();
};

#endif // COLLECTION_H
