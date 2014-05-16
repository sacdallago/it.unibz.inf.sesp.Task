#ifndef TASKUTILITIES_H
#define TASKUTILITIES_H

#include "collection.h"
#include <QList>
#include <QString>
#include <QVariant>

namespace TaskUtilities{
    /*!
     * \brief Relates two tasks
     * \param predecessor, is the predecessor in the relation (father)
     * \param successor, is the successor in the relation (the child)
     * \return returns false if the relation to be established forms a cycle! True elsewise.
     */
    bool relate(Task *predecessor, Task *successor);
    /*!
     * \brief printList prints the list of tasks in a Qlist
     * \return the string to be printed
     */
    QString printList(QList<Task*>*);
    /*!
     * \brief tasksFromQuery popoulates a collection from a database query
     * \param col the collection to be populated
     * \param query the query "select id, name, importance,.... from task"
     */
    void tasksFromQuery(Collection * col, const QMap<QString, QList<QVariant> *> * query);
    /*!
     * \brief relateFromQuery relates the tasks in a collection from a database query
     * \param col the collection from where to take the tasks to be related
     * \param query the query "select father, child from relation"
     */
    void relateFromQuery(Collection * col, const QMap<QString, QList<QVariant> *> * query);
}

#endif // TASKUTILITIES_H
