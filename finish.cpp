#include "finish.h"

finish::finish(QWidget *parent) : QDialog (parent)
{
    exit = new QPushButton();
    again = new QPushButton();
    message = new QLabel();

    layout1 = new QHBoxLayout();
    layout2 = new QHBoxLayout();
    layout3 = new QVBoxLayout();

    exit->setText(tr("Exit (Alt+&b)"));
    again->setText(tr("Restart (Alt+&r)"));
    message->setText(tr("Do you want to restart a new game?"));
    layout1->addStretch();
    layout1->addWidget(message);
    layout1->addStretch();
    layout2->addStretch();
    layout2->addWidget(again);
    layout2->addStretch();
    layout2->addWidget(exit);
    layout2->addStretch();
    layout3->addLayout(layout1);
    layout3->addLayout(layout2);

    connect(exit, SIGNAL(clicked()), this, SLOT(exitClicked()));
    connect(again, SIGNAL(clicked()), this, SLOT(restartClicked()));

    setLayout(layout3);
    setFixedWidth(sizeHint().width()+100);
    setFixedHeight(sizeHint().height());
    setWindowTitle(tr("Game over!"));
}

finish::~finish()
{
    delete exit;    delete again;
    delete message; delete layout1;
    delete layout2; delete layout3;
}

void finish::exitClicked(){
    qDebug() << "Finish.exitClicked.";
    emit gameExit();
    this->close();
}

void finish::restartClicked(){
    qDebug() << "Finish.restartClicked.";
    emit restart();
    this->close();
}
