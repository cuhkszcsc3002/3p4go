#include "transfer.h"
#include <QtWidgets>

transfer::transfer(QWidget *parent) : QDialog (parent){
    message = new QLabel;
    layout = new QVBoxLayout;

    message->setText(tr("Waiting other user to proecss your invite. Please wait..."));
    layout->addWidget(message);

    setLayout(layout);
    setFixedWidth(sizeHint().width()+100);
    setFixedHeight(sizeHint().height());
    setWindowTitle(tr("Strating a new 3P4GO..."));
}

transfer::~transfer()
{
    delete message;
    delete layout;
}



