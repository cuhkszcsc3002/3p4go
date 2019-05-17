#include "reject.h"

reject::reject(QWidget *parent) : QDialog (parent)
{
    exit = new QPushButton();
    message = new QLabel();
    QHBoxLayout *layout1 = new QHBoxLayout;
    QVBoxLayout *layout2 = new QVBoxLayout;

    exit->setText(tr("Exit (Alt+&b)"));
    message->setText(tr("PlayXXX reject you invite!"));
    layout1->addStretch();
    layout1->addWidget(message);
    layout1->addStretch();
    layout2->addLayout(layout1);
    layout2->addWidget(exit);

    connect(exit, SIGNAL(clicked()), this, SLOT(exitClicked()));

    setLayout(layout2);
    setFixedWidth(sizeHint().width()+200);
    setFixedHeight(sizeHint().height());
    setWindowTitle(tr("Oupps..."));
}

reject::~reject(){}

void reject::exitClicked(){
    this->close();
}

//void reject::receiveReject(){
//    this->show();
//}
