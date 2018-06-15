#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QVariant>
#include <QSqlResult>

class Connection
{
public:
    static bool is_open(){return instance().db.open();}
    static Connection& instance()
    {
        static Connection* _instance = 0;
        if(_instance==0)
            _instance = new Connection();
        return *_instance;
    }
    bool check_login(QString login, const QString& password)
    {
        //return true;
        if(!db.open()) return false;
        QSqlQuery q;
        q.prepare("select * from users where name=:login and pass=:pass");
        q.bindValue(":login",login);
//        q.bindValue(":pass",QVariant(password));
        q.bindValue(":pass",QString(QCryptographicHash::hash(password.toUtf8(),
            QCryptographicHash::Md5).toHex()));
        q.exec();
        q.last();
        if(q.at()==0) return true;
        return false;
    }
private:
    QSqlDatabase db;
    Connection()
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("/home/xtrim/Projects/qt/tasker/tasker");
    }
};

#endif // CONNECTION_H
