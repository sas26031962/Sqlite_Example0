#include "ccontrolincoming.h"

cControlIncoming::cControlIncoming(QGroupBox *group_box_parent, QObject *parent) : QObject(parent)
{
    gbParent = group_box_parent;

    QGridLayout * layout = new QGridLayout(gbParent);

    lbAuthor = new QLabel(gbParent);
    lbAuthor->setText("Author");
    lbAuthor->setAlignment(Qt::AlignCenter);

    lbSerial = new QLabel(gbParent);
    lbSerial->setText("Serial");
    lbSerial->setAlignment(Qt::AlignCenter);

    lbName = new QLabel(gbParent);
    lbName->setText("Name");
    lbName->setAlignment(Qt::AlignCenter);

    leAuthor = new QLineEdit(gbParent);
    leAuthor->setText("Author_text");

    leSerial = new QLineEdit(gbParent);
    leSerial->setText("Serial_text");

    leName = new QLineEdit(gbParent);
    leName->setText("Name_text");

    leRequest = new QLineEdit(gbParent);
    leRequest->setText("Request_text");

    layout->addWidget(lbAuthor, 0,0);
    layout->addWidget(lbSerial, 0,1);
    layout->addWidget(lbName, 0,2);

    layout->addWidget(leAuthor, 1,0);
    layout->addWidget(leSerial, 1,1);
    layout->addWidget(leName, 1,2);

    layout->addWidget(leRequest, 2,0,1,3);

    int Margin = 3;
    layout->setContentsMargins(Margin, Margin, Margin, Margin);
}

cControlIncoming::~cControlIncoming()
{

}

QString cControlIncoming::getRequest()
{
    return leRequest->text();
}


QString cControlIncoming::getAuthor()
{
    return leAuthor->text();
}

QString cControlIncoming::getSerial()
{
    return leSerial->text();
}

QString cControlIncoming::getName()
{
    return leName->text();
}
