#ifndef MOREDIALOG_H
#define MOREDIALOG_H

#include <QDialog>
#include "taskwidget.h"
#include <QVBoxLayout>
#include <mainwindow.h>

namespace Ui {
class MoreDialog;
}

class MoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoreDialog(QWidget *parent = 0, Collection *coll = NULL);
    ~MoreDialog();

    TaskWidget *getWt() const;
    void setWt(TaskWidget *value);
    /*!
     * \brief fillWidget Fills all the fields in the current widget with the info of the Task passed as a parameter
     * \param t Task which attributes will be displayed
     */
     void fillWidget(Task *t);

     Ui::MoreDialog *getUi() const;
     void setUi(Ui::MoreDialog *value);


     /**
     * @brief MoreDialog::on_buttonBox_accepted Saves the changes
     */
     void on_buttonBox_accepted();
    /**
    * @brief MoreDialog::getTitle getter for the title
    * @return
    */
     QString getTitle() const;
     /**
    * @brief MoreDialog::getDescription getter for the description
    * @return
    */
     QString getDescription() const;

    /**
    * @brief MoreDialog::getPriority getter for the priority
    * @return
    */
     qint64  getPriority() const;
     /**
    * @brief MoreDialog::getEffort getter for the effort/hours
    * @return
    */
     qint64  getEffort() const;
    /**
    * @brief MoreDialog::getT getter for the task pointer
    * @return
    */
     Task *getT() const;
    /**
    * @brief MoreDialog::setT setter for the task pointer
    * @param value
    */
     void setT(Task *value);

     MainWindow *getMain() const;
     void setMain(MainWindow *value);

         QList<QCheckBox*> *cblist;
private slots:
     void on_buttonBox_rejected();

private:
     Ui::MoreDialog *ui;
     Task *t;
     QVBoxLayout *lslayout;

    Collection *tasks;
    QList<Task *> *dlist;
    /*!
     * \brief getDependList get the task predecessors list
     */
    void getDependList();

};

#endif // MOREDIALOG_H
