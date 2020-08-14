#include "mydatabase.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QDir>
#include <QDebug>


MyDatabase::MyDatabase()
{

}


/**
 * 初始化数据库
 * @brief MyDatabase::initDatabase
 */
void MyDatabase::open(){

    // 准备处理数据库
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString currentPath = QDir::currentPath();
    QString dbFile = currentPath + "/database/store3.db";

    qInfo() << dbFile;
    db.setDatabaseName(dbFile);

    bool b = db.open();    

    // 如果数据库文件存在
    if(b){
        qDebug() << "open database succeed !";

    }else{
        qDebug() << db.lastError();
    }

}

void MyDatabase::close(){
    db.close();
}
