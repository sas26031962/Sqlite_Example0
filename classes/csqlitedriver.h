#ifndef CSQLITEDRIVER_H
#define CSQLITEDRIVER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QDebug>
#include <tuple>

class cSqliteDriver : public QObject
{
    Q_OBJECT

    //Атрибуты
    QString qsName = "SqliteDriver";
    QString qsMessage;
    QString qsDatabaseName = "audiobooks.db";

public:
    QString qsTableName = "books";

    QSqlDatabase db;
    //QSqlQuery query;

    //Конструкторы и деструкторы
    explicit cSqliteDriver(QObject *parent = 0);
    ~cSqliteDriver();

    //Методы
    bool openDatabase();
    bool closeDatabase();
    bool dropTable();
    bool createTable();
    bool insertRecord(std::tuple<QString, QString, QString> data);
    bool selectAllAndShow();
    void showSelectionResult(QSqlQuery query);

signals:

public slots:
};

#endif // CSQLITEDRIVER_H
