#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <iostream>

int main()
{
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    try
    {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", ""); // Select the desired database
        con->setSchema("testing_cpp");
        stmt = con->createStatement();
        std::string username = "John";
        std::string password = "password123";
        std::string query = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + password + "')";
        stmt->execute(query);
        delete stmt;
        delete con;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "SQL Exception: " << e.what() << std::endl;
        std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
    }
    catch (std::runtime_error &e)
    {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    return 0;
}