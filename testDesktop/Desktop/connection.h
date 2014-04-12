#ifndef CONNECTION_H
#define CONNECTION_H
#include <iostream>
#include <QtSql>
#include <QString>
#include <QtSql/QSqlResult>
#include "task.h"

using namespace std;
class Connection {
private:
    QSqlDatabase db;
public:
    /*!
     * \brief Creates the connection
     * \param driver is the driver to be used (QMYSQL, QPSQL, QODBC, etc)
     * \param server is the server address
     * \param db the name of the database
     * \param username the username for that database
     * \param password the password to access that database for that user
     */
    Connection(QString driver = "QPSQL", QString server = "ufficio.zucchitours.com", QString db = "sesp_task", QString username = "sesp_tasker", QString password = "7m6wvT&0");

    /*!
     * \brief Closes the connection to the database.
     * \return returns true if the connection has been closed, otherwise false!
     */
    bool close();

    QMap<QString,QList<QVariant>* > select(QString relation, QList<QString>* = NULL ,QList<QString>* wheres = NULL);

    QString whereCreator(QList<QString>* w = NULL);
    QString filterCreator(QList<QString>);
    QList<QString> *getColumnNames(QString relation);
    QString printQuery(const QMap<QString,QList<QVariant>* >*, bool verbose = false);

    //Project related
    Task* getTask(qint64 id);
    Task* insertTask(QString name, qint64 importance, qint64 duration, QString description, qint64 status);

    //destroyer closes connection my default
    ~Connection();
};

#endif // CONNECTION_H
