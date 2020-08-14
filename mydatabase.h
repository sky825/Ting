#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QSql>
#include <QSqlDatabase>


class MyDatabase
{
public:
    MyDatabase();    
    void open();
    void close();
    QSqlDatabase db;
private:


};

#endif // MYDATABASE_H
