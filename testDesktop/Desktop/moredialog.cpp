#include "moredialog.h"
#include "ui_moredialog.h"
#include <QtGui>

MoreDialog::MoreDialog(QWidget *parent, TaskWidget *wt) :
    QDialog(parent),
    ui(new Ui::MoreDialog)
{
    this->wt = wt;
    ui->setupUi(this);
    lslayout = new QVBoxLayout(ui->scrollAreaWidgetContents);


}


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


TaskWidget *MoreDialog::getWt() const
{
    return wt;
}

void MoreDialog::setWt(TaskWidget *value)
{
    wt = value;
}

