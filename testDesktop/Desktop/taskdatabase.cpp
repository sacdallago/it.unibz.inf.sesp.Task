#include "taskdatabase.h"

TaskDatabase::TaskDatabase(QString driver, QString server, QString db, QString username, QString password) : Connection(driver,server,db,username,password){
    userID = 0;
    cout << "Remember to login." << endl;
}

bool TaskDatabase::login(QString taskUser, QString taskPassword){
    QList<QString> where, fil;

    where.append("username = '" + taskUser + "'");
    where.append("password = '" + taskPassword + "'");

    fil.append("id");

    try {
        QMap<QString, QList<QVariant> *> check  = Connection::select("auth",&fil,&where);
        if(!check.isEmpty()){
            userID = check.first()->first().toInt();
            cout << "User ID: " << userID << endl;
        } else {
            cout << "User not found!!" << endl;
        }
    } catch (...){
    }
}

void TaskDatabase::logout(){
    userID = 0;
}


Task* TaskDatabase::getTask(qint64 id){
    if(userIF != 0){
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
    } else {
        return NULL;
    }
}

Task* TaskDatabase::insertTask(QString name, qint64 importance, qint64 duration, QString description, qint64 status){
    if(userIF != 0){
        QSqlQuery query;
        QString q = "INSERT INTO task (name, importance, duration, description, status) VALUES('"+name+"',"+QString::number(importance)+","+QString::number(duration)+",'"+description+"',"+QString::number(status)+") RETURNING id;";
        cout << "Executing query: "<< q.toUtf8().constData() << endl;
        bool successful = query.exec(q);
        if(!successful){
            return NULL;
        }
        query.next();
        return getTask(query.value(0).toInt());
    } else {
        return NULL;
    }
}

bool TaskDatabase::deleteRelation(qint64 father, qint64 child){
    if(userIF != 0){
        QSqlQuery query;
        QString q = "DELETE FROM relation WHERE father = " + QString::number(father) + " AND child = " + QString::number(child) + ";";
        cout << "Executing query: "<< q.toUtf8().constData() << endl;
        return query.exec(q);
    } else {
        return false;
    }
}

bool TaskDatabase::insertRelation(qint64 father, qint64 child){
    if(userIF != 0){
        QSqlQuery query;
        QString q = "INSERT INTO relation VALUES (" + QString::number(father) + "," + QString::number(child) + ");";
        cout << "Executing query: "<< q.toUtf8().constData() << endl;
        return query.exec(q);
    } else {
        return false;
    }
}

bool TaskDatabase::insertRelations(Task *father){
    if(userIF != 0){
        QString q = "";
        for(Task *child : *father->getPredecessors()){
            q += "INSERT INTO relation VALUES (" + QString::number(father->getId()) + "," + QString::number(child->getId()) + ");\n";
        }
        QSqlQuery query;
        cout << "Executing query: "<< q.toUtf8().constData() << endl;
        return query.exec(q);
    } else {
        return false;
    }
}

bool TaskDatabase::insertRelations(QList<Task *> *fathers, QList<Task *> *children){
    if(userIF != 0){
        QString q = "";
        for(Task *father : *fathers){
            for(Task *child : *children){
                q += "INSERT INTO relation VALUES (" + QString::number(father->getId()) + "," + QString::number(child->getId()) + ");\n";
            }
        }
        QSqlQuery query;
        cout << "Executing query: "<< q.toUtf8().constData() << endl;
        return query.exec(q);
    } else {
        return false;
    }
}


bool TaskDatabase::removeTask(Task *t){
    if(userIF != 0){
        QSqlQuery query;
        QString q = "DELETE FROM task WHERE id=" + QString::number(t->getId()) + ";";
        cout << "Executing query: "<< q.toUtf8().constData() << endl;
        return query.exec(q);
    } else {
        return false;
    }
}

bool TaskDatabase::update(Task *modified){
    if(userIF != 0){
        QSqlQuery query;
        QString q = "UPDATE SET (name, importance, duration, description, status) = ('"+modified->getName()+"',"+QString::number(modified->getImportance())+","+QString::number(modified->getDurationInH())+",'"+modified->getDescription()+"',"+QString::number(modified->getStatus())+") FROM task WHERE id=" + QString::number(modified->getId()) + ";";
        cout << "Executing query: "<< q.toUtf8().constData() << endl;
        return query.exec(q);
    } else {
        return false;
    }
}

bool TaskDatabase::clear(){
    if(userIF != 0){
        QSqlQuery query;
        QString q = "DELETE FROM task;DELETE FROM relation;";
        cout << "Executing query: "<< q.toUtf8().constData() << endl;
        return query.exec(q);
    } else {
        return false;
    }
}

QString TaskDatabase::printQuery(const QMap<QString, QList<QVariant> *> *query, bool verbose){
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
