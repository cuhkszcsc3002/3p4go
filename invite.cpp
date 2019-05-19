#include "invite.h"
#include <QtWidgets>

inviteReceive::inviteReceive(QWidget *parent) : QDialog (parent)
{
    this->resize(QSize(500,150));

    acceptInvite = new QPushButton(tr("Accept (Alt+&a)"));
    rejectInvite = new QPushButton(tr("Reject (Alt+&r)"));

    info = new QLabel();
    QString infoString = QString("Player from ") + QString("wants to invite you for a new 3P4Go game.");
    info->setText(infoString);

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
{
    delete acceptInvite;    delete rejectInvite;
    delete info;            delete button;
    delete information;     delete mainLayout;
}

//
void inviteReceive::receiveInvite(const QString ipAddress)
{
    qDebug() << "Invite.receiveInvite";
    QString message = "Player " + ipAddress +  " wants to invite you for a new 3P4Go game.";
    this->info->setText(message);
    this->show();
    qDebug() << "Invite.receiveInvite Pass";

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
