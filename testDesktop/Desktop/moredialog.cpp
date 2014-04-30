#include "moredialog.h"
#include "ui_moredialog.h"
#include <QtGui>
#include <iostream>

/**
 * @brief MoreDialog::MoreDialog
 * @param parent
 * @param TaskWidget wt
 */
using namespace std;

MoreDialog::MoreDialog(QWidget *parent, TaskWidget *wt) :
    QDialog(parent),
    ui(new Ui::MoreDialog)
{
    this->wt = wt;
    ui->setupUi(this);
    lslayout = new QVBoxLayout(ui->scrollAreaWidgetContents);

}

/**
 * @brief MoreDialog::getDependList creates a QLabel list of predecessors for a single task
 */
void MoreDialog::getDependList(){

    for ( Task *father : *t->getPredecessors()) {

        QLabel *l = new QLabel(father->getName());
        lslayout->addWidget(l);

    }

}




MoreDialog::~MoreDialog()
{
    delete ui;
}

/**
 * @brief MoreDialog::fillWidget fills the editable widget with task information
 * @param Task t
 */
void MoreDialog::fillWidget(Task *t)
{
    ui->titleLabel->setText(t->getName());
    ui->descriptionText->setText(t->getDescription());
    ui->prioritySpinBox->setValue(t->getImportance());
    ui->durationSpinBox->setValue(t->getDurationInH());

    this->t = t;
    getDependList();

}

/**
 * @brief MoreDialog::getDescription get the description of a Task in plain text from the More Widget
 * @return QString
 */
QString MoreDialog::getDescription() const {

   return ui->descriptionText->toPlainText();
}

/**
 * @brief MoreDialog::getTitle get the title from the More Widget
 * @return QString
 */
QString MoreDialog::getTitle() const {

    return ui->titleLabel->toPlainText();
}

/**
 * @brief MoreDialog::getPriority
 * @return qint64
 */
qint64 MoreDialog::getPriority() const {

    return ui->prioritySpinBox->value();
}

/**
 * @brief MoreDialog::getEffort
 * @return qint64
 */
qint64 MoreDialog::getEffort() const {

    return ui->durationSpinBox->value();
}

Ui::MoreDialog *MoreDialog::getUi() const
{
    return ui;
}

void MoreDialog::setUi(Ui::MoreDialog *value)
{
    ui = value;
}


TaskWidget *MoreDialog::getWt() const
{
    return wt;
}

void MoreDialog::setWt(TaskWidget *value)
{
    wt = value;
}

