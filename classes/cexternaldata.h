#ifndef CEXTERNALDATA_H
#define CEXTERNALDATA_H

#include <QObject>
#include <QString>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QClipboard>
#include <QApplication>
#include <QStringList>

#include "classes/csqlitedriver.h"

class cExternalData : public QObject
{
    Q_OBJECT

    //Атрибуты
    QGroupBox * gbParent;

    QLineEdit * leCurrentString;
    QPushButton * pbPrevious;
    QPushButton * pbNext;

    QStringList qslDataList;
    QString qsFileName = "/data/ExternalText.txt";

    int CurrentIndex = 0;

public:
    explicit cExternalData(QGroupBox * group_box_parent, QObject *parent = 0);
    ~cExternalData();

signals:

public slots:
};

#endif // CEXTERNALDATA_H
