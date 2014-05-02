#include "logindialog.h"
#include "ui_logindialog.h"


LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_buttonBox_accepted()
{
   user = ui->userLineEdit->text();
   password = ui->passwordLineEdit->text();
}

void LoginDialog::on_buttonBox_rejected()
{

}

void LoginDialog::setMessage(QString *message){

    ui->messageLabel->setText(*message);
}

Ui::LoginDialog *LoginDialog::getUi() const
{
    return ui;
}

void LoginDialog::setUi(Ui::LoginDialog *value)
{
    ui = value;
}

QString LoginDialog::getPassword() const
{
    return password;
}

void LoginDialog::setPassword(const QString &value)
{
    password = value;
}

QString LoginDialog::getUser() const
{
    return user;
}

void LoginDialog::setUser(const QString &value)
{
    user = value;
}

