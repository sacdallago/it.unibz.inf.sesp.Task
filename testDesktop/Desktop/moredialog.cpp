#include "moredialog.h"
#include "ui_moredialog.h"
#include <QtGui>


MoreDialog::MoreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoreDialog)
{
    ui->setupUi(this);
    lslayout = new QVBoxLayout(ui->scrollAreaWidgetContents);


}

/**
 * @brief MoreDialog::getDependList get the task predecessors list
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
 * @brief MoreDialog::fillWidget fills the widget from the Task elements.
 * @param Task t
 */
void MoreDialog::fillWidget(Task *t)
{

    this->t = t;
    ui->titleLabel->setText(t->getName());
    ui->descriptionText->setText(t->getDescription());
    ui->prioritySpinBox->setValue(t->getImportance());
    ui->durationSpinBox->setValue(t->getDurationInH());

    getDependList();

}

/**
 * @brief MoreDialog::getDescription getter for the description
 * @return
 */
QString MoreDialog::getDescription() const {

   return ui->descriptionText->toPlainText();
}

/**
 * @brief MoreDialog::getTitle getter for the title
 * @return
 */
QString MoreDialog::getTitle() const {

    return ui->titleLabel->toPlainText();
}

/**
 * @brief MoreDialog::getPriority getter for the priority
 * @return
 */
qint64 MoreDialog::getPriority() const {

    return ui->prioritySpinBox->value();
}

/**
 * @brief MoreDialog::getEffort getter for the effort/hours
 * @return
 */
qint64 MoreDialog::getEffort() const {


    return ui->durationSpinBox->value();
}

/**
 * @brief MoreDialog::getT getter for the task pointer
 * @return
 */
Task *MoreDialog::getT() const
{
    return t;
}

/**
 * @brief MoreDialog::setT setter for the task pointer
 * @param value
 */
void MoreDialog::setT(Task *value)
{
    t = value;
}



Ui::MoreDialog *MoreDialog::getUi() const
{
    return ui;
}

void MoreDialog::setUi(Ui::MoreDialog *value)
{
    ui = value;
}

