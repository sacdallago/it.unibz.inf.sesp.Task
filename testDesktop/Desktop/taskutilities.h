#ifndef TASKUTILITIES_H
#define TASKUTILITIES_H

#include "task.h"

namespace TaskUtilities{
    /*!
     * \brief Relates two tasks
     * \param predecessor, is the predecessor in the relation (father)
     * \param successor, is the successor in the relation (the child)
     * \return returns false if the relation to be established forms a cycle! True elsewise.
     */
    bool relate(Task *predecessor, Task *successor);
}

#endif // TASKUTILITIES_H
