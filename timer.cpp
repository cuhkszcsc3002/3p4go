#include "timer.h"
#include <string>
#include <iostream>

using namespace std;

timer::timer(QWidget *parent) : QWidget (parent)
{
    /* The time that allow user to think, you can modify it*/
    initSecond = 0;
    initMinute = 2;

    tinyTimer = new QTimer(this);
    tinyTimer->start(0);
    tinyTimer->setInterval(1000);   //every 1000 millisecond will raise a timeout signal

    message = new QLabel;
    separator = new QLabel;
    second = new QLabel;
    minute = new QLabel;
    hLayout = new QHBoxLayout;
    vLayout = new QVBoxLayout;

    QFont font1("Microsoft YaHei", 20, 20); //first arrtibute is the word style, second is word size, third is B
    message->setText(tr("The time remaining: "));
    QFont font2("Microsoft YaHei", 20, 75);
    separator->setText(tr(":"));
    separator->setFrameShape (QFrame::Box);
    separator->setStyleSheet("border-width:1px; border-style:solid; border-color:rgb(255, 170, 0);");
    separator->setFont(font2);
    second->setText(QString::number(initSecond));
    second->setFrameShape (QFrame::Box);
    second->setStyleSheet("border-width:1px; border-style:solid; border-color:rgb(255, 170, 0);");
    second->setFont(font2);
    minute->setText(QString::number(initMinute));
    minute->setFrameShape (QFrame::Box);
    minute->setStyleSheet("border-width:1px; border-style:solid; border-color:rgb(255, 170, 0);");
    minute->setFont(font2);

    hLayout->addStretch();
    hLayout->addWidget(minute);
    hLayout->addWidget(separator);
    hLayout->addWidget(second);
    hLayout->addStretch();
    vLayout->addStretch();
    vLayout->addWidget(message);
    vLayout->addStretch();
    vLayout->addLayout(hLayout);
    vLayout->addStretch();

    connect(tinyTimer, SIGNAL(timeout()), this, SLOT(onCount()));

    setLayout(vLayout);
    setFixedWidth(sizeHint().width()+100);
    setFixedHeight(sizeHint().height()+50);
    setWindowTitle(tr("Cautions! Timer is on..."));
}

timer::~timer(){}

void timer::onCount()
{
    if (initSecond == 1 && initMinute == 0)
    {
        /* Time out!!!! */
        initSecond--;
        second->setText("0" + QString::number(initSecond));
        /* Should emit a signal here */
        this->update();
    }
    else if (initSecond == 0 && initMinute != 0)
    {
        initMinute--;
        initSecond = 60;
        if (initMinute < 10)
            minute->setText("0" + QString::number(initMinute));
        else
            minute->setText(QString::number(initMinute));
        second->setText(QString::number(initSecond));
        this->update();
    }
    else if (initSecond != 0)
    {
        initSecond--;
        if (initSecond < 10 && initSecond >= 0)
            second->setText("0" + QString::number(initSecond));
        else
            second->setText(QString::number(initSecond));
        this->update();
    }
}
