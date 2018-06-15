#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    login_dlg = new LoginDialog(this);
    //    login_dlg->setParent(this,Qt::Widget);
    login_dlg->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //Подключаем базу данных
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/xtrim/Projects/qt/tasker/tasker");
    if(!db.open()) return;

    //Осуществляем запрос
//    QSqlQuery query;
//    query.exec("SELECT id, name, pass FROM users");

    QSqlQuery query;
    query.prepare("select * from users where name=:login and pass=:pass");
    query.bindValue(":login","admin");
//    query.bindValue(":pass","user");
    query.bindValue(":pass",QString(QCryptographicHash::hash(QString("admin").toUtf8(),QCryptographicHash::Md5).toHex()));
    query.exec();

    ui->textEdit->insertPlainText(query.lastError().text());
    //Выводим значения из запроса
    while (query.next())
    {
        QString tasker_id = query.value(0).toString();
        QString tasker_name = query.value(1).toString();
        QString tasker_pass = query.value(2).toString();
        QString tasker_pass_md5 = QString(QCryptographicHash::hash(query.value(2).toString().toUtf8(),QCryptographicHash::Md5).toHex());
        ui->textEdit->insertPlainText(tasker_id+" "+tasker_name+" "+tasker_pass+" "+tasker_pass_md5+"\n");
    }
}
