#ifndef RELATIONS_H
#define RELATIONS_H

#include <QDialog>
#include "ui_relations.h"
#include "task.h"
#include "taskwidget.h"
#include "mainwindow.h"
#include "collection.h"
#include "connection.h"
#include "taskutilities.h"

namespace Ui {
class Relations;
}

class Relations : public QDialog
{
    Q_OBJECT

public:
	/*!
     * \brief Relations create a Dialog that enables the user to set the dependencies of a task with others
     * \param parent
     * \param coll The collection containing the tasks
     */
    explicit Relations(QWidget *parent = 0, Collection* coll = NULL);
    ~Relations();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Relations *ui;
    Collection* coll;
    QList<Task*> toDoList;
};

#endif // RELATIONS_H






