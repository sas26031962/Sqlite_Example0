#include "csqlitedriver.h"

cSqliteDriver::cSqliteDriver(
        QTableView *table_view,
        QTextBrowser *text_browser_log,
        QGroupBox * groub_box_incoming,
        QComboBox *history,
        QObject *parent
        ) : QObject(parent)
{
    TableView = table_view;
    tbLog = text_browser_log;
    gbIncoming = groub_box_incoming;
    cbHistory = history;

    QHeaderView * VerticalHeader = TableView->verticalHeader();

    connect(TableView, &QTableView::clicked, this, &cSqliteDriver::onTableViewClicked);
    connect(VerticalHeader, &QHeaderView::sectionClicked, this, &cSqliteDriver::onTableViewActivated);
    connect(cbHistory, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &cSqliteDriver::onHistoryIndexChanged);

    ControlIncoming = new cControlIncoming(gbIncoming);

    qDebug() << "Accessable drivers: " << QSqlDatabase::drivers();
    qDebug() << "cSqliteDriver ctor";

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(qsDatabaseName);

    qslRequests = cLoadFiles::loadStringListFromFile(qsRequestsFileName);

    qsMessage = "SqliteDriver > Load from ";
    qsMessage += qsRequestsFileName;
    qsMessage += " ";
    qsMessage += QString::number(qslRequests.count());
    qsMessage += " lines";
    qDebug() << qsMessage;
    tbLog->append(qsMessage);

    cbHistory->addItems(qslRequests);
    ControlIncoming->setRequest(qslRequests.at(0));
}

cSqliteDriver::~cSqliteDriver()
{
    qDebug() << "cSqliteDriver dector";

}

bool cSqliteDriver::openDatabase()
{
    bool x = db.open();
    qsMessage = qsName;
    qsMessage += " > Open ";
    qsMessage += qsDatabaseName;
    if (x)
    {
        qsMessage += " database success.";
    }
    else
    {
        qsMessage += " error:";
        qsMessage += db.lastError().text();
    }
    qDebug() << qsMessage;
    tbLog->append(qsMessage);

    return x;
}

bool cSqliteDriver::closeDatabase()
{
    db.close();
    qsMessage = qsName;
    qsMessage += " > Connection close.";
    qDebug() << qsMessage;
    tbLog->append(qsMessage);

    return true;
}

bool cSqliteDriver::dropTable()
{
    bool x = true;

    QString qsDropTable = "";
    qsDropTable += "DROP TABLE IF EXISTS ";
    qsDropTable += qsTableName;

    QSqlQuery query;
    x = query.exec(qsDropTable);
    qsMessage = qsName;
    qsMessage += " > Drop table ";
    if(x)
    {
        qsMessage += qsTableName;
        qsMessage += " complete.";
    }
    else
    {
        qsMessage += "error:";
        qsMessage += query.lastError().text();
    }
    qDebug() << qsMessage;
    tbLog->append(qsMessage);

    return x;
}

bool cSqliteDriver::createTable()
{
    QString qsRequestCreateTable = "";
    qsRequestCreateTable += "CREATE TABLE IF NOT EXISTS ";
    qsRequestCreateTable += qsTableName;                                //Имя таблицы
    qsRequestCreateTable += " (";
    qsRequestCreateTable += "id";                                       //Id
    qsRequestCreateTable += " INTEGER PRIMARY KEY AUTOINCREMENT, ";
    qsRequestCreateTable += "author";                                   //Автор
    qsRequestCreateTable += " TEXT NOT NULL, ";
    qsRequestCreateTable += "serial";                                   //Серия
    qsRequestCreateTable += " TEXT, ";
    qsRequestCreateTable += "name";                                     //Название
    qsRequestCreateTable += " TEXT NOT NULL)";

    QSqlQuery query;

    bool x = query.exec(qsRequestCreateTable);

    qsMessage = qsName;
    qsMessage += " > Create table: ";
    qsMessage += qsTableName;
    if(x)
    {
        qsMessage += " is ready.";
    }
    else
    {
        qsMessage += " error:";
        qsMessage += query.lastError().text();
    }

    qDebug() << qsMessage;
    tbLog->append(qsMessage);

    return x;
}

bool cSqliteDriver::insertRecord(std::tuple<QString, QString, QString> data)
{
    QString qsInsertData = "";
    qsInsertData += "INSERT INTO ";
    qsInsertData += qsTableName;
    qsInsertData += " (author, serial, name) VALUES (:author, :serial, :name)";

    qDebug() << "InsertRecord> data: Author=" << std::get<0>(data) << " Serial=" << std::get<1>(data) << " Book=" << std::get<2>(data);
    QSqlQuery query;
    query.prepare(qsInsertData);
    query.bindValue(":author", std::get<0>(data));//"AuthorName"
    query.bindValue(":serial", std::get<1>(data));//"SerialName"
    query.bindValue(":name", std::get<2>(data));//"BookName"

    bool x = query.exec();
    qsMessage = qsName;
    qsMessage += " > Insert data to the table ";
    qsMessage += qsTableName;
    qsMessage += ": Data insert";
    if (x)
    {
        QSqlQuery query;
        QString qsSelecCount = "SELECT COUNT(*) FROM ";
        qsSelecCount += qsTableName;
        query.exec(qsSelecCount);
        int rowCount = 0;
        if (query.next())
        {
            rowCount = query.value(0).toInt();

            qsMessage += " success!";
            qsMessage += " RowCount=";
            qsMessage += QString::number(rowCount);
        }
        else
        {
            x = false;
        }
    }
    else
    {
        qsMessage +=  " error:";
        qsMessage += query.lastError().text();
    }

    qDebug() << qsMessage;
    tbLog->append(qsMessage);

    return x;
}

bool cSqliteDriver::selectAllAndShow()
{
    QString qsSelectData = "";
    qsSelectData += "SELECT id, author, serial, name FROM ";
    qsSelectData += qsTableName;
    qsSelectData += ";";

    QSqlQuery query;

    bool x = query.exec(qsSelectData);

    qsMessage = qsName;
    qsMessage += " > Select data from the table ";
    qsMessage += qsTableName;
    qsMessage += ": Data select";
    if (x)
    {
        qsMessage += " success!";
        //---
        showSelectionResult(query);
        //---
    }
    else
    {
        qsMessage +=  " error:";
        qsMessage += query.lastError().text();
    }

    qDebug() << qsMessage;
    tbLog->append(qsMessage);

    return x;
}

bool cSqliteDriver::selectAllAndViewInTable()
{
    QString qsSelectData = "";
    qsSelectData += "SELECT author, serial, name FROM ";
    qsSelectData += qsTableName;

    QSqlQueryModel * model = new QSqlQueryModel();

    bool x;

    model->setQuery(qsSelectData);
    if (model->lastError().isValid())
    {
        qCritical() << model->lastError().text();
        x = false;
    }
    else
    {
        x = true;
        qDebug() << "SelectAllAndViewInTable > Model rows count=" << model->rowCount();
        for (int row = 0; row < model->rowCount(); ++row)
        {
            QSqlRecord record = model->record(row);
            QString qsAuthor = record.value("author").toString();
            QString qsSerial = record.value("serial").toString();
            QString qsBook = record.value("name").toString();
            qDebug() << qsAuthor << qsSerial << qsBook;
        }

        TableView->setModel(model);
        TableView->show();
    }
    qsMessage = qsName;
    qsMessage += " > Select data from the table ";
    qsMessage += qsTableName;
    qsMessage += ": Data select";
    if (x)
    {
        qsMessage += " success!";
        //---
        //showSelectionResult(query);
        //---
    }
    else
    {
        qsMessage +=  " error:";
        //qsMessage += query.lastError().text();
    }

    qDebug() << qsMessage;
    tbLog->append(qsMessage);

    return x;
}

bool cSqliteDriver::execRequest()
{
    QString qsExecRequest = ControlIncoming->getRequest();

    qsMessage = qsName;
    if(qslRequests.contains(qsExecRequest))
    {
        qsMessage += " > contains this request";
    }
    else
    {
        qslRequests.append(qsExecRequest);
        qsMessage += " > append this request";
    }
    qDebug() << qsMessage;
    tbLog->append(qsMessage);

    QSqlQueryModel * model = new QSqlQueryModel();

    bool x;

    model->setQuery(qsExecRequest);
    if (model->lastError().isValid())
    {
        qCritical() << model->lastError().text();
        x = false;
    }
    else
    {
        x = true;
        TableView->setModel(model);
        TableView->show();
    }
    qsMessage = qsName;
    qsMessage += " > Select data from the table ";
    qsMessage += qsTableName;
    qsMessage += ": Data select";
    if (x)
    {
        qsMessage += " success!";
    }
    else
    {
        qsMessage +=  " error:";
        qsMessage += model->lastError().text();
    }

    qDebug() << qsMessage;
    tbLog->append(qsMessage);

    return x;
}

void cSqliteDriver::showSelectionResult(QSqlQuery query)
{
    qDebug() << "\nBooks list:";
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString author = query.value(1).toString();
        QString serial = query.value(2).toString();
        QString name = query.value(3).toString();
        qDebug() << "ID:" << id << ", Author:" << author << ", Serial:" << serial <<", Name:" << name;
    }
}

QString cSqliteDriver::getAuthor()
{
    return ControlIncoming->getAuthor();
}

QString cSqliteDriver::getSerial()
{
    return ControlIncoming->getSerial();
}

QString cSqliteDriver::getName()
{
    return ControlIncoming->getName();
}

void cSqliteDriver::onTableViewClicked(const QModelIndex &index)
{
    QString Message = "TableViewClicked > ";
    if(index.isValid())
    {
        QString data = index.data().toString();
        int row = index.row();
        int col = index.column();

        Message += "Data=";
        Message += data;
        Message += " Row=";
        Message += QString::number(row);
        Message += " Column=";
        Message += QString::number(col);
        //qDebug() << "Clicked:" << data << " row=" << row << " col" << col;

        switch(col)
        {
            case 0:
                ControlIncoming->setAuthor(data);
            break;

            case 1:
                ControlIncoming->setSerial(data);
            break;

            case 2:
                ControlIncoming->setName(data);
            break;

            default:
                Message += "Wrong row index:";
                Message += QString::number(col);
            break;
        }
    }
    else
    {
        Message += "Model index is not valid";
    }
    tbLog->append(Message);
}

void cSqliteDriver::onTableViewActivated(int logical_row)
{
    //qDebug() << "TableViewActivated" << logical_row;

    // Получаем данные из модели
    QAbstractItemModel *model = TableView->model();
        if (!model) return;

        // Например, читаем ID из первого столбца
        QModelIndex idIndex = model->index(logical_row, 0);
        int id = model->data(idIndex).toInt();

        QString author = model->data(model->index(logical_row, 0)).toString();
        QString serial = model->data(model->index(logical_row, 1)).toString();
        QString name = model->data(model->index(logical_row, 2)).toString();

        qDebug() << "Выбрана запись> " << id << " Author:" << author << " Serial: " << serial << " Name:" << name;

        ControlIncoming->setAuthor(author);
        ControlIncoming->setSerial(serial);
        ControlIncoming->setName(name);
}

bool cSqliteDriver::setAuthor()
{
    qDebug() << "SqliteDriver: setAuthor()";
    ControlIncoming->setAuthorFromClipboard();
    return true;
}

bool cSqliteDriver::setSerial()
{
    qDebug() << "SqliteDriver: setSerial()";
    ControlIncoming->setSerialFromClipboard();
    return true;
}

bool cSqliteDriver::setName()
{
    qDebug() << "SqliteDriver: setName()";
    ControlIncoming->setNameFromClipboard();
    return true;
}

bool cSqliteDriver::storeRequestHistory()
{
    return cLoadFiles::saveStringListToFile(qsRequestsFileName, qslRequests);
}

void cSqliteDriver::onHistoryIndexChanged(int index)
{
    qDebug() << "SqligeDriver > History index changed: " << index;
    ControlIncoming->setRequest(qslRequests.at(index));
}
