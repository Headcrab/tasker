#include "logindialog.h"
#include "ui_logindialog.h"
#include "connection.h"

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
    Connection& c = Connection::instance();
    if(c.check_login(ui->lineEdit->text(),ui->lineEdit_2->text())){
        close();
    }else{
        ui->label->setText("Login or password incorrect. Please try again");
        QPalette p = ui->label->palette();
        p.setColor(QPalette::WindowText,Qt::red);
        ui->label->setPalette(p);
        show();
    }
}

void LoginDialog::on_buttonBox_rejected()
{
   QApplication::quit();
}

