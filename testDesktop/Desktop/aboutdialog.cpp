#include "aboutdialog.h"
#include "ui_aboutdialog.h"

/** This class generates a dialog with the information
	relative to the developers and the program itself.
*/
AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_buttonBox_accepted()
{
    this->close();
}
