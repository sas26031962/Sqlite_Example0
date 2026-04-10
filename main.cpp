#include "mainwindow.h"
#include <QApplication>

#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*
    cSqliteDriver * SqliteDriver = new cSqliteDriver();

    //--- Пытаемся открыть базу данных

    if(!SqliteDriver->openDatabase()) return 1;

    //---

    if(!SqliteDriver->dropTable()) return 1;

    //---
    if(!SqliteDriver->createTable()) return 1;

    //---
    auto t1 = std::make_tuple("AuthorName", "SerialName", "BookName");
    if(!SqliteDriver->insertRecord(t1)) return 1;

    auto t2 = std::make_tuple("Александр Пушкин", "Повести Белкина", "Метель");
    if(!SqliteDriver->insertRecord(t2)) return 1;

    auto t3 = std::make_tuple("Оноре де Бальзак", "Человеческая комедия", "Гобсек");
    if(!SqliteDriver->insertRecord(t3)) return 1;

    //---
    if(!SqliteDriver->selectAllAndShow()) return 1;

    //---Закрытие базы данных

    SqliteDriver->closeDatabase();

    //---
*/
    MainWindow w;
    w.show();

    return a.exec();
}

