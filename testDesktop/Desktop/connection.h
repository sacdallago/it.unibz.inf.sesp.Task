#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql>
#include <QString>

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

    //destroyer closes connection my default
    ~Connection();
};

#endif // CONNECTION_H
