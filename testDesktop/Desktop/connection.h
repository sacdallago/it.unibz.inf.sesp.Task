#ifndef CONNECTION_H
#define CONNECTION_H
#include <iostream>
#include <QtSql>
#include <QString>
#include <QtSql/QSqlResult>
#include "task.h"

class Connection {
protected:
    QSqlDatabase db;
    /*!
     * \brief whereCreator creates a string representing the "where" part of a sql query
     * \param w a list of where conditions, su as "age > 30".
     * \return a string representing the "where" part of a sql query
     */
    QString whereCreator(QList<QString>* w = NULL);
    /*!
     * \brief filterCreator creates a string representing the select conditions. For example, if you pass a list containing
     * "id", "age", it will create a string "id,age" to put in the "select" clause of the sql query.
     * \return a string representing the "select" part of the query
     */
    QString filterCreator(QList<QString>);
    /*!
     * \brief getColumnNames creates a string representing the select conditions such that they map every column in the database.
     * \param relation the name of the table to map the columns
     * \return a string representing the "select" part of the query
     */
    QList<QString> *getColumnNames(QString relation);
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

    /*!
     * \brief select performs select operation on database
     * \param relation a strig representing the table or relation, such as "professors"
     * \param columns a pointer to a list of strings, by default set to null (will query the database to get all the column names
     * for the given table). If you want to select the "id" and "age" from the table professors, here you would bass a pointer to
     * a list containing l[1]="id", l[2]="age".
     * \param wheres a pointer to a list of strings, by default se to null, so that no filtering applies to the result set. Works
     * as the columns parameter.
     * \return returns a map where the key is the column name and the value a list of untipified variables
     */
    QMap<QString,QList<QVariant>* > select(QString relation, QList<QString>* columns= NULL ,QList<QString>* wheres = NULL);
    /*!
     * \brief select performs select operation on database
     * \param relation a strig representing the table or relation, such as "professors"
     * \param wheres a string representing a condition, such as "age > 30"
     * \return
     */
    QMap<QString,QList<QVariant>* > select(QString relation, QString wheres);

    /*!
     * \brief printQuery fed with a query, will print every value in it in the columns indicated by the key
     * \param verbose prints the thole thing to the cout destination
     * \return returns the printed query as string, for further user
     */
    QString printQuery(const QMap<QString,QList<QVariant>* >*, bool verbose = false);

    ~Connection();
};

#endif // CONNECTION_H
