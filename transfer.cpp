#include "transfer.h"
#include <QtWidgets>
//#include <QDialog>
//#include <QLayout>
//#include <QPushButton>

transfer::transfer(QWidget *parent) : QDialog (parent)
{
    comfirm = new QPushButton;
    QLabel *message = new QLabel;
    QVBoxLayout *layout = new QVBoxLayout;

    comfirm->setText(tr("Comfirm"));
    message->setText(tr("Waiting other user to start a new game. Please wait..."));
    layout->addWidget(message);
    layout->addWidget(comfirm);

    connect(comfirm, SIGNAL(clicked()), this, SLOT(comfirmClicked()));

    setLayout(layout);
    setFixedWidth(sizeHint().width()+100);
    setFixedHeight(sizeHint().height());
    setWindowTitle(tr("Strating a new 3P4GO..."));
}

transfer::~transfer(){}

void transfer::receiveInvite(){
    this->show();
}

void transfer::comfirmClicked(){
    emit comfirmReceived();
    this->hide();
}


