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

QString Connection::filterCreator(QList<QString> filters){
    if(filters.size() == 0){
        return "* ";
    } else {
        QString result;
        for(int i=0;i<filters.size();i++){
            result += filters.value(i) + ", ";
        }
        result = result.left(result.size()-2) + " ";
        return result;
    }
    return "*";
}

QList<QString>* Connection::getColumnNames(QString relation) {
    QList<QString> *result = new QList<QString>();
    QSqlQuery q;

    cout << "Executing query: SELECT column_name FROM information_schema.columns WHERE table_name = '" << relation.toUtf8().constData() << "';" << endl;
    q.exec("SELECT column_name FROM information_schema.columns WHERE table_name = '" + relation + "';");
    while (q.next()){
        result->append(q.value(0).toString());
    }
    return result;
}

QMap<QString, QList<QVariant>* > Connection::select(QString relation, QList<QString>* filters, QList<QString>* wheres){
    QMap<QString, QList<QVariant>* > result;
    QString filter, where;
    if(filters == NULL || filters->size() == 0){
        filters = getColumnNames(relation);
    }
    filter = filterCreator(*filters);
    if(wheres == NULL){
        where = "";
    } else {
        where = whereCreator(wheres);
    }

    QString q = "SELECT " + filter + "FROM " + relation + " " + where + ";";

    cout << "Executing query: "<< q.toUtf8().constData() << endl;
    QSqlQuery query;
    query.exec(q);
    while(query.next()){
        int i = 0;
        for(QString s : *filters){
            if(!result.contains(s)){
                result.insert(s,new QList<QVariant>());
            }
            result.value(s)->append(query.value(i));
            i++;
        }
    }
    return result;
}

Task* Connection::getTask(qint64 id){
    QList<QString> where;
    where.append("id=" + QString::number(id));
    QMap<QString, QList<QVariant>* > task = select("task",NULL,&where);
    qint64 importance = task.value("importance")->value(0).toInt();
    qint64 durationInH = task.value("duration")->value(0).toInt();
    QString name = task.value("name")->value(0).toString();
    QString description = task.value("description")->value(0).toString();
    qint64 status = task.value("status")->value(0).toInt();
    QString time = task.value("creation")->value(0).toString();
    return new Task(id,importance,durationInH,name,description,status,time);
}

Task* Connection::insertTask(QString name, qint64 importance, qint64 duration, QString description, qint64 status){
    QSqlQuery query;
    QString q = "INSERT INTO task (name, importance, duration, description, status) VALUES('"+name+"',"+QString::number(importance)+","+QString::number(duration)+",'"+description+"',"+QString::number(status)+") RETURNING id;";
    cout << "Executing query: "<< q.toUtf8().constData() << endl;
    bool successful = query.exec(q);
    if(!successful){
        return NULL;
    }
    query.next();
    return getTask(query.value(0).toInt());
}

bool Connection::deleteRelation(qint64 father, qint64 child){
    QSqlQuery query;
    QString q = "DELETE FROM relation WHERE father = " + QString::number(father) + " AND child = " + QString::number(child) + ";";
    cout << "Executing query: "<< q.toUtf8().constData() << endl;
    return query.exec(q);
}

bool Connection::insertRelation(qint64 father, qint64 child){
    QSqlQuery query;
    QString q = "INSERT INTO relation VALUES (" + QString::number(father) + "," + QString::number(child) + ");";
    cout << "Executing query: "<< q.toUtf8().constData() << endl;
    return query.exec(q);
}

bool Connection::insertRelations(Task *father){
    QString q = "";
    for(Task *child : *father->getPredecessors()){
        q += "INSERT INTO relation VALUES (" + QString::number(father->getId()) + "," + QString::number(child->getId()) + ");\n";
    }
    QSqlQuery query;
    cout << "Executing query: "<< q.toUtf8().constData() << endl;
    return query.exec(q);
}

bool Connection::insertRelations(QList<Task *> *fathers, QList<Task *> *children){
    QString q = "";
    for(Task *father : *fathers){
        for(Task *child : *children){
                q += "INSERT INTO relation VALUES (" + QString::number(father->getId()) + "," + QString::number(child->getId()) + ");\n";
            }
    }
    QSqlQuery query;
    cout << "Executing query: "<< q.toUtf8().constData() << endl;
    return query.exec(q);
}

QString Connection::printQuery(const QMap<QString, QList<QVariant> *> *query, bool verbose){
    QString result="";
    for (QString s : query->keys()){
        result += s + "\t\t";
        foreach (QVariant t, *query->value(s)){
            result += t.toString() + "\t";
        }
        result += "\n";
    }
    if(verbose){
        cout << result.toUtf8().constData();
    }
    return result;
}

bool Connection::removeTask(Task *t){
    QSqlQuery query;
    QString q = "DELETE FROM task WHERE id=" + QString::number(t->getId()) + ";";
    cout << "Executing query: "<< q.toUtf8().constData() << endl;
    return query.exec(q);
}

bool update(Task *modified){
    QSqlQuery query;
    QString q = "DELETE FROM task WHERE id=" + QString::number(t->getId()) + ";";
    cout << "Executing query: "<< q.toUtf8().constData() << endl;
    return query.exec(q);
}

Connection::~Connection(){
    close();
}
