#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"

const string server   = "dallago.co"; //???
const string username = "sesp_tasker";
const string password = "7m6wvT&0";

connection::connection()
{
        sql::Driver     *driver; // Create a pointer to a MySQL driver object
        sql::Connection *dbConn; // Create a pointer to a database connection object
        sql::Statement  *stmt;   // Create a pointer to a Statement object to hold our SQL commands
        sql::ResultSet  *res;    // Create a pointer to a ResultSet object to hold the results of any queries we run

    // Try to get a driver to use to connect to our DBMS
    try
    {
        driver = get_driver_instance();
    }
    catch (sql::SQLException e)
    {
        cout << "Could not get a database driver. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

    // Try to connect to the DBMS server
    try
    {
        dbConn = driver->connect(server, username, password);
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to database. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

    stmt = dbConn->createStatement(); // Specify which connection our SQL statement should be executed on

    // Try to query the database
    try
    {
        stmt->execute("USE sesp_task");              // Select which database to use. Notice that we use "execute" to perform a command.
        res = stmt->executeQuery("SELECT * FROM task");
    }
    catch (sql::SQLException e)
    {
        cout << "SQL error. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

    // While there are still results (i.e. rows/records) in our result set...
    while (res->next())
    {
        // ...get each field we want and output it to the screen
        // Note: The first field/column in our result-set is field 1 (one) and -NOT- field 0 (zero)
        // Also, if we know the name of the field then we can also get it directly by name by using:
        // res->getString("TheNameOfTheField");
        cout << res->getString(1) << endl;
    }

    // Clean up after ourselves
    delete res;
    delete stmt;
    delete dbConn;

    system("pause");
    return 0;
}
