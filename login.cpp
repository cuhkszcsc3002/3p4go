#include "login.h"



login::login(QWidget *parent) : QWidget (parent)
{
    ip = new char[16];
    //GetLocalIP(ip);
    ipAddress = ip;
    myIP = ip;

    this->resize(QSize(600,400));

    invite = new QPushButton(tr("Start 3P4GO (Alt+&s)"));
    exit = new QPushButton(tr("Exit (Alt+&e)"));
    check = new QPushButton(tr("Check Score (Alt+&c)"));

    p1ip = new QLabel(tr("Player1 IP address: "));
    p2ip = new QLabel(tr("Player2 IP address: "));
    p1port = new QLabel(tr("Port: "));
    p2port = new QLabel(tr("Port: "));
    host = new QLabel(tr("Host"));


    player1IP = new QLineEdit();
    player2IP = new QLineEdit();
    player1Port = new QLineEdit();
    player2Port = new QLineEdit();
    hostIP = new QLineEdit();
    hostIP->setText(myIP); //alternate: QString::fromStdString(ipAddress)

//    player1IP->setMaxLength(25);
    player1IP->setAlignment(Qt::AlignLeft);
//    player1IP->setFixedWidth(250);

//    player2IP->setMaxLength(25);
    player2IP->setAlignment(Qt::AlignLeft);
//    player2IP->setFixedWidth(250);

    player1Port->setAlignment(Qt::AlignLeft);
    player2Port->setAlignment(Qt::AlignLeft);

    hostIP->setMaxLength(25);
    hostIP->setAlignment(Qt::AlignLeft);
    hostIP->setFixedWidth(250);
    hostIP->setReadOnly(true);

    p1Layout = new QHBoxLayout;
    p2Layout = new QHBoxLayout;
    hostLayout = new QHBoxLayout;

    port1Layout = new QHBoxLayout;
    port2Layout = new QHBoxLayout;

    p1IPLayout = new QHBoxLayout;
    p2IPLayout = new QHBoxLayout;
    p1PortLayout = new QHBoxLayout;
    p2PortLayout = new QHBoxLayout;
    hostIPLayout = new QHBoxLayout;

    editorLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;

    ipLayout = new QVBoxLayout;
    portLayout = new QVBoxLayout;
    userLayout = new QVBoxLayout;
    userPortlayout = new QVBoxLayout;
    mainLayout = new QVBoxLayout;

    p1Layout->addStretch();
    p1Layout->addWidget(p1ip);
    p1Layout->addStretch();
    p2Layout->addStretch();
    p2Layout->addWidget(p2ip);
    p2Layout->addStretch();
    hostLayout->addStretch();
    hostLayout->addWidget(host);
    hostLayout->addStretch();
    userLayout->addLayout(p1Layout);
    userLayout->addLayout(p2Layout);
//    userLayout->addLayout(hostLayout);

    port1Layout->addStretch();
    port1Layout->addWidget(p1port);
    port1Layout->addStretch();
    port2Layout->addStretch();
    port2Layout->addWidget(p2port);
    port2Layout->addStretch();
    userPortlayout->addLayout(port1Layout);
    userPortlayout->addLayout(port2Layout);

    p1IPLayout->addWidget(player1IP);
    p1IPLayout->addStretch();
    p2IPLayout->addWidget(player2IP);
    p2IPLayout->addStretch();
    hostIPLayout->addWidget(hostIP);
    hostIPLayout->addStretch();
    ipLayout->addLayout(p1IPLayout);
    ipLayout->addLayout(p2IPLayout);
//    ipLayout->addLayout(hostIPLayout);

    p1PortLayout->addWidget(player1Port);
    p1PortLayout->addStretch();
    p2PortLayout->addWidget(player2Port);
    p2PortLayout->addStretch();
    portLayout->addLayout(p1PortLayout);
    portLayout->addLayout(p2PortLayout);

    editorLayout->addLayout(userLayout);
    editorLayout->addLayout(ipLayout);
    editorLayout->addLayout(userPortlayout);
    editorLayout->addLayout(portLayout);

    buttonLayout->addStretch();
    buttonLayout->addWidget(invite);
    buttonLayout->addStretch();
    buttonLayout->addWidget(check);
    buttonLayout->addStretch();
    buttonLayout->addWidget(exit);
    buttonLayout->addStretch();

    mainLayout->addLayout(editorLayout);
    mainLayout->addLayout(buttonLayout);

    connect(exit, SIGNAL(clicked()), this, SLOT(exitClick()));
    connect(invite, SIGNAL(clicked()), this, SLOT(inviteClicked()));
    connect(check, SIGNAL(clicked()), this, SLOT(checkScoreClick()));

    setLayout(mainLayout);
    setWindowTitle(tr("Starting a new 3P4GO..."));
}

login::~login()
{}

void login::exitClick()
{
    this->close();
}

void login::checkScoreClick()
{
    emit showScore();
}

void login::inviteClicked()
{
    QString p1IP = player1IP->text();
    QString p2IP = player2IP->text();
    QString p1Port = player1Port->text();
    QString p2Port = player2Port->text();

    emit showTransfer();
    emit emitInvite(p1IP, p2IP, p1Port, p2Port);
}

void login::startReceived()
{
    this->hide();
}

