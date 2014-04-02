#include "connection.h"

Connection::Connection(QString driver, QString server, QString db, QString username, QString password) {
    this->db = QSqlDatabase::addDatabase(driver);
    this->db.setHostName(server);
    this->db.setDatabaseName(db);
    this->db.setUserName(username);
    this->db.setPassword(password);
}

bool Connection::close(){
    if(db.open()){
        db.close();
        return true;
    }
    return false;
}

Connection::~Connection(){
    close();
}
