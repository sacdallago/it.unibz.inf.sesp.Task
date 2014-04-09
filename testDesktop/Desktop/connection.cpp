#include "connection.h"

using namespace std;
Connection::Connection(QString driver, QString server, QString db, QString username, QString password) {
    this->db = QSqlDatabase::addDatabase(driver);
    this->db.setHostName(server);
    this->db.setDatabaseName(db);
    this->db.setUserName(username);
    this->db.setPassword(password);
    this->db.open();
}

bool Connection::close(){
    if(db.open()){
        db.close();
        return true;
    }
    return false;
}



QString** Connection::selectQuery(QString s){
    QSqlQuery query;
    query.exec(s);
    int i = 0;
    QString **ret;
    ret = new QString*[query.size()];

    while (query.next()){
        ret[i] = new QString[query.numRowsAffected()];
        for (int j = 0; j<query.numRowsAffected(); j++){
            ret[i][j] = query.value(j).toString();
            cout << query.value(j).constData();
        }
        i=i+1;
    }
    return ret;
}

bool Connection::insertTask(QString id, QString name, qint64 importance, qint64 duration, QString description, qint64 status, qint64 relatives){
    QSqlQuery query;
    bool ret = query.exec((QString(
   "INSERT INTO task (id, name, importance, duration, description, status, relatives) "
   "VALUES('%1','%2','%3','%4','%5','%6','%7')").arg(id).arg(name).arg(importance).arg(duration).arg(description).arg(status).arg(relatives)));
    return ret;
}



Connection::~Connection(){
    close();
}
