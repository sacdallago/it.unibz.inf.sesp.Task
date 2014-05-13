#ifndef ADDTASKDIALOG_H
#define ADDTASKDIALOG_H

#include "collection.h"
#include <QDialog>

namespace Ui {
class AddTaskDialog;
}

class AddTaskDialog : public QDialog
{
    Q_OBJECT

public:
	/*!
     * \brief This class creates a Dialog that enables the user to insert the info related to a new Task and to add this new task to the DB.
	\param parent
	\param coll The collection containing the Tasks
	*/
    explicit AddTaskDialog(QWidget *parent = 0, Collection *coll = NULL);
    ~AddTaskDialog();

private slots:
	/*!
     * \brief on_buttonBox_accepted Creates the new Task and puts it in the DB.
     */
    void on_buttonBox_accepted();
	/*!
     * \brief on_buttonBox_rejected Closes the window
     */
    void on_buttonBox_rejected();

private:
    Ui::AddTaskDialog *ui;
    /*!
     * \brief coll is the collection containing the tasks
     */
    Collection* coll;
};

#endif // ADDTASKDIALOG_H
