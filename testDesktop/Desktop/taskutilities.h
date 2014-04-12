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
    QString printList(QList<Task*>*);
    void tasksFromQuery(Collection *, const QMap<QString, QList<QVariant> *> *);
    void relateFromQuery(Collection *, const QMap<QString, QList<QVariant> *> *);
}

#endif // TASKUTILITIES_H
