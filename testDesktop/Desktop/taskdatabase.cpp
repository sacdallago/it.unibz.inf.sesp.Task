#include "taskdatabase.h"

TaskDatabase::TaskDatabase(QString driver, QString server, QString db, QString username, QString password) : Connection(driver,server,db,username,password){
    userID = 0;
    cout << "Remember to login." << endl;
}

bool TaskDatabase::login(QString taskUser, QString taskPassword){
    QList<QString> where, fil;

    where.append("username = '" + taskUser + "'");
    where.append("password = '" + taskPassword + "'");

    fil.append("username");

    try {
        QMap<QString, QList<QVariant> *> check  = Connection::select("auth",&fil,&where);
        if(!check.isEmpty()){
            userID = 1;
            username = check.first()->first().toString();
            cout << "User found" << endl;
            return true;
        } else {
            userID = 0;
            username = "";
            cout << "User not found!!" << endl;
            return false;
        }
    } catch (...){
        return false;
    }
}

bool TaskDatabase::createUser(QString taskUser, QString taskPassword){
    QSqlQuery query;
    QString q = "INSERT INTO auth VALUES ('" + taskUser + "','" + taskPassword + "');";
    cout << "Executing query: "<< q.toUtf8().constData() << endl;
    query.prepare(q);
    return query.exec();
}

bool TaskDatabase::deleteUser(QString taskUser){
    QSqlQuery query;
    QString q = "DELETE FROM auth WHERE username = '" + taskUser + "';";
    cout << "Executing query: "<< q.toUtf8().constData() << endl;
    query.prepare(q);
    return query.exec();
}

void TaskDatabase::logout(){
    userID = 0;
}


Task* TaskDatabase::getTask(qint64 id){
    if(userID != 0){
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
    if(userID != 0){
        QSqlQuery query;
        QString q = "INSERT INTO task (name, importance, duration, description, status, username) VALUES('"+name+"',"+QString::number(importance)+","+QString::number(duration)+",'"+description+"',"+QString::number(status)+",'"+username+"') RETURNING id;";
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
    if(userID != 0){
        QSqlQuery query;
        QString q = "DELETE FROM relation WHERE father = " + QString::number(father) + " AND child = " + QString::number(child) + ";";
        cout << "Executing query: "<< q.toUtf8().constData() << endl;
        return query.exec(q);
    } else {
        return false;
    }
}

bool TaskDatabase::insertRelation(qint64 father, qint64 child){
    if(userID != 0){
        QSqlQuery query;
        QString q = "INSERT INTO relation VALUES (" + QString::number(father) + "," + QString::number(child) + ");";
        cout << "Executing query: "<< q.toUtf8().constData() << endl;
        return query.exec(q);
    } else {
        return false;
    }
}

bool TaskDatabase::insertRelations(Task *father){
    if(userID != 0){
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
    if(userID != 0){
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
    if(userID != 0){
        QSqlQuery query;
        QString q = "DELETE FROM task WHERE id=" + QString::number(t->getId()) + ";";
        cout << "Executing query: "<< q.toUtf8().constData() << endl;
        return query.exec(q);
    } else {
        return false;
    }
}

bool TaskDatabase::update(Task *modified){
    if(userID != 0){
        QSqlQuery query;
        QString q = "UPDATE SET (name, importance, duration, description, status) = ('"+modified->getName()+"',"+QString::number(modified->getImportance())+","+QString::number(modified->getDurationInH())+",'"+modified->getDescription()+"',"+QString::number(modified->getStatus())+") FROM task WHERE id=" + QString::number(modified->getId()) + ";";
        cout << "Executing query: "<< q.toUtf8().constData() << endl;
        return query.exec(q);
    } else {
        return false;
    }
}

bool TaskDatabase::clear(){
    if(userID != 0){
        QSqlQuery query;
        QString q = "DELETE FROM task; DELETE FROM relation; DELETE FROM auth";
        cout << "Executing query: "<< q.toUtf8().constData() << endl;
        return query.exec(q);
    } else {
        return false;
    }
}
