#include "invite.h"
#include <QtWidgets>

inviteReceive::inviteReceive(QWidget *parent) : QDialog (parent)
{
    this->resize(QSize(500,150));

    acceptInvite = new QPushButton(tr("Accept (Alt+&a)"));
    rejectInvite = new QPushButton(tr("Reject (Alt+&r)"));

    info = new QLabel();
    info->setText("Player XXX wants to invite you for a new 3P4Go game.");

    button = new QHBoxLayout();
    information = new QHBoxLayout();
    mainLayout = new QVBoxLayout();

    button->addStretch();
    button->addWidget(acceptInvite);
    button->addStretch();
    button->addWidget(rejectInvite);
    button->addStretch();
    information->addStretch();
    information->addWidget(info);
    information->addStretch();
    mainLayout->addLayout(information);
    mainLayout->addLayout(button);

    connect(acceptInvite, SIGNAL(clicked()), this, SLOT(acceptClick()));
    connect(rejectInvite, SIGNAL(clicked()), this, SLOT(rejectClick()));

    setWindowTitle(tr("New Game Invitation..."));
    //setFixedWidth(sizeHint().width()+100);
    //setFixedHeight(sizeHint().height());
    setLayout(mainLayout);
}

inviteReceive::~inviteReceive()
{}

//
void inviteReceive::receiveInvite(const QString ipAddress)
{
    QString message = "Player " + ipAddress +  " wants to invite you for a new 3P4Go game.";
    info = new QLabel(message);
    this->show();

}
//

void inviteReceive::acceptClick()
{
    emit inviteAccept();
    this->close();
}

void inviteReceive::rejectClick()
{
    emit inviteReject();
    this->close();
}
