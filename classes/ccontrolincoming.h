#ifndef CCONTROLINCOMING_H
#define CCONTROLINCOMING_H

#include <QObject>
#include <QString>
#include <QGroupBox>
#include "QGridLayout"
#include <QLabel>
#include <QLineEdit>

class cControlIncoming : public QObject
{
    Q_OBJECT

    //Атрибуты
    QGroupBox * gbParent;
    QLabel * lbAuthor;
    QLabel * lbSerial;
    QLabel * lbName;

    QLineEdit * leAuthor;
    QLineEdit * leSerial;
    QLineEdit * leName;

    QLineEdit * leRequest;

public:
    //Конструкторы и деструкторы
    explicit cControlIncoming(QGroupBox * group_box_parent, QObject *parent = 0);
    ~cControlIncoming();

    //Методы
    QString getRequest();
    QString getAuthor();
    QString getSerial();
    QString getName();

signals:

public slots:
};

#endif // CCONTROLINCOMING_H
