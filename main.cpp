#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QTextCodec>
#include "mydatabase.h"

int main(int argc, char *argv[])
{

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//情况2

    QTextCodec::setCodecForLocale(codec);


    // 读取配置文件
    QString currentPath = QDir::currentPath();
    qDebug() << "current application path : " + currentPath;

    MyDatabase db;
    db.open();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
