#ifndef CSQLITEDRIVER_H
#define CSQLITEDRIVER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QTableView>
#include <QModelIndex>
#include <QTextBrowser>
#include <QGroupBox>
#include <QHeaderView>
#include <QAbstractItemModel>
#include <QComboBox>

#include <tuple>

#include "classes/ccontrolincoming.h"
#include "classes/cloadfiles.h"

class cSqliteDriver : public QObject
{
    Q_OBJECT

    //Атрибуты
    QString qsName = "SqliteDriver";
    QString qsMessage;
    QString qsDatabaseName = "audiobooks.db";
    QString qsRequestsFileName = "SQL_Requests.txt";
    QStringList qslRequests;

    QTableView * TableView;
    QTextBrowser* tbLog;
    QGroupBox * gbIncoming;
    cControlIncoming * ControlIncoming;
    QComboBox * cbHistory;

public:
    QString qsTableName = "books";

    QSqlDatabase db;

    //Конструкторы и деструкторы
    explicit cSqliteDriver(QTableView * table_view, QTextBrowser* text_browser_log, QGroupBox * groub_box_incoming, QComboBox * history, QObject *parent = 0);
    ~cSqliteDriver();

    //Методы
    bool openDatabase();
    bool closeDatabase();
    bool dropTable();
    bool createTable();
    bool insertRecord(std::tuple<QString, QString, QString> data);
    bool selectAllAndShow();
    bool selectAllAndViewInTable();
    bool execRequest();
    void showSelectionResult(QSqlQuery query);
    QString getAuthor();
    QString getSerial();
    QString getName();
    bool setAuthor();
    bool setSerial();
    bool setName();
    bool storeRequestHistory();

signals:

public slots:
    void onTableViewClicked(const QModelIndex &index);
    void onTableViewActivated(int logical_row);
    void onHistoryIndexChanged(int index);
};

#endif // CSQLITEDRIVER_H
