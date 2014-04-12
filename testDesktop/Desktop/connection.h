#ifndef CONNECTION_H
#define CONNECTION_H
#include <iostream>
#include <QtSql>
#include <QString>
#include <QtSql/QSqlResult>

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

    QMap<QString,QList<QString>* > select(QString relation, QList<QString>* = NULL ,QList<QString>* wheres = NULL);
    bool insertTask(QString id, QString name, qint64 importance, qint64 duration, QString description, qint64 status, qint64 relatives);

    QString whereCreator(QList<QString>* w = NULL);
    QString filterCreator(QList<QString>* f = NULL);
    QList<QString> *getColumnNames(QString relation);

    //destroyer closes connection my default
    ~Connection();
};

#endif // CONNECTION_H
