#include "cexternaldata.h"

cExternalData::cExternalData(QGroupBox *group_box_parent, QObject *parent) : QObject(parent)
{
    gbParent = group_box_parent;

    QHBoxLayout * layout = new QHBoxLayout(gbParent);

    int Height = 20;
    int ButtonWidth = Height;

    leCurrentString = new QLineEdit(gbParent);
    leCurrentString->setText("Current_data_text");
    leCurrentString->setMinimumHeight(Height);
    leCurrentString->setMaximumHeight(Height);

    pbPrevious = new QPushButton(gbParent);
    pbPrevious->setText("<");
    pbPrevious->setMinimumHeight(Height);
    pbPrevious->setMaximumHeight(Height);
    pbPrevious->setMinimumWidth(ButtonWidth);
    pbPrevious->setMaximumWidth(ButtonWidth);
    pbPrevious->setCursor(Qt::PointingHandCursor);

    pbNext = new QPushButton(gbParent);
    pbNext->setText(">");
    pbNext->setMinimumHeight(Height);
    pbNext->setMaximumHeight(Height);
    pbNext->setMinimumWidth(ButtonWidth);
    pbNext->setMaximumWidth(ButtonWidth);
    pbNext->setCursor(Qt::PointingHandCursor);

    layout->addWidget(pbPrevious);
    layout->addWidget(pbNext);
    layout->addWidget(leCurrentString);

    int Margin = 3;
    layout->setContentsMargins(Margin, Margin, Margin, Margin);

    qslDataList = cLoadFiles::loadStringListFromFile(cSqliteDriver::qsApplicationPath + qsFileName);
    if(qslDataList.count() > 0)
    {
        leCurrentString->setText(qslDataList.at(CurrentIndex));
    }
    else
    {
        leCurrentString->setText("External data file is empty, nothing to show");
    }

    connect(pbPrevious, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Previous' click";
        CurrentIndex--;
        if(CurrentIndex < 0) {CurrentIndex = 0;}

        leCurrentString->setText(qslDataList.at(CurrentIndex));
    });

    connect(pbNext, static_cast<void(QPushButton::*)()>(&QPushButton::pressed),this, [this](){
        qDebug() << "PushButton 'Next' click";
        CurrentIndex++;
        if(CurrentIndex == qslDataList.count()) {CurrentIndex--;}

        leCurrentString->setText(qslDataList.at(CurrentIndex));
    });

}

cExternalData::~cExternalData()
{

}
