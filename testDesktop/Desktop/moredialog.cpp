#include "moredialog.h"
#include "ui_moredialog.h"
#include <QtGui>


MoreDialog::MoreDialog(QWidget *parent, Collection *coll) :
    QDialog(parent),
    ui(new Ui::MoreDialog)
{
    this->tasks = coll;
    cblist = new QList<QCheckBox*>();
    ui->setupUi(this);
    lslayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
}

void MoreDialog::getDependList(){

    for ( Task *father : *t->getPredecessors()) {
       QCheckBox *l = new QCheckBox();
       l->setText(father->getName());
       l->setChecked(true);
       cblist->append(l);
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

QString MoreDialog::getDescription() const {
   return ui->descriptionText->toPlainText();
}

QString MoreDialog::getTitle() const {
    return ui->titleLabel->toPlainText();
}

qint64 MoreDialog::getPriority() const {
    return ui->prioritySpinBox->value();
}

qint64 MoreDialog::getEffort() const {
    return ui->durationSpinBox->value();
}

Task *MoreDialog::getT() const
{
    return t;
}

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

void MoreDialog::on_buttonBox_accepted()
{
    //for each checkbox (relation)
    for(QCheckBox *c : *cblist){
        //if it is unchecked
        if(!c->isChecked()){
            //identify the task in the predecessors list by comparing
            //the name of the unchecked task and all the other tasks
            for ( Task *father : *t->getPredecessors()) {
                if(father->getName().compare(c->text())==0){
                    //unrelate the checked task (father) with the
                    //current task
                    tasks->unrelate(father,this->t);
                }
            }
        }
    }
}