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


/*
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
*/

QString Connection::whereCreator(QList<QString> *wheres){
    if(wheres == NULL || wheres->size() == 0){
        return "";
    } else if (wheres->size() == 1){
        return "WHERE " + wheres->value(0);
    } else {
        QString result = "WHERE " + wheres->value(0) + " ";
        for(int i=1;i<wheres->size();i++){
            result += "AND " + wheres->value(i) + " ";
        }
        return result;
    }
    return "";

}

QString Connection::filterCreator(QList<QString> *filters){
    if(filters == NULL || filters->size() == 0){
        return "*";
    } else {
        QString result;
        for(int i=0;i<filters->size();i++){
            result += filters->value(i) + ", ";
        }
        result = result.left(result.size()-2) + " ";
        return result;
    }
    return "*";
}

QList<QString>* Connection::getColumnNames(QString relation) {
    QList<QString>* result = new QList<QString>();
    QSqlQuery q;
    try{
        cout << "Executing query: SELECT column_name FROM information_schema.columns WHERE table_name = '" << relation.toUtf8().constData() << "';" << endl;
        q.exec("SELECT column_name FROM information_schema.columns WHERE table_name = '" + relation + "';");
        while (q.next()){
            result->append(q.value(0).toString());
        }
    } catch (QSqlError er){
        //error
    }
    return result;
}

QMap<QString, QList<QString>* > Connection::select(QString relation, QList<QString>* filters,QList<QString>* wheres){
    QMap<QString, QList<QString>* > result;
    QString filter, where;
    if(filters == NULL){
        filters = new QList<QString>(*getColumnNames(relation));
    }
    filter = filterCreator(filters);
    cout << (filters == NULL) << endl;
    if(wheres == NULL){
        where = "";
    } else {
        where = whereCreator(wheres);
    }

    QString q = "SELECT " + filter + "FROM '" + relation + "' " + where + ";";

    cout << "Executing query: "<< q.toUtf8().constData() << endl;
    QSqlQuery query;
    query.exec(q);
    while(query.next()){
        int i = 0;
        for(QString s : *filters){
            if(!result.contains(s)){
                result.insert(s,new QList<QString>());
            }
            result.value(s)->append(query.value(i).toString());
            i++;
        }
    }
    //cout << (filters == NULL) << endl;
    return result;
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
