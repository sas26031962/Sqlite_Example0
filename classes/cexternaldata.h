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

class cExternalData : public QObject
{
    Q_OBJECT

    //Атрибуты
    QGroupBox * gbParent;

    QLineEdit * leCurrentString;
    QPushButton * pbPrevious;
    QPushButton * pbNext;

public:
    explicit cExternalData(QGroupBox * group_box_parent, QObject *parent = 0);
    ~cExternalData();

signals:

public slots:
};

#endif // CEXTERNALDATA_H
