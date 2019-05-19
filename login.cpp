#include "login.h"
#include "game.h"

login::login(QWidget *parent) : QWidget (parent)
{
    qDebug()<<"login.login: constructing login class...";
    this->resize(QSize(700,700));

    invite = new QPushButton(tr("Start 3P4GO (Alt+&s)"));
    exit = new QPushButton(tr("Exit (Alt+&e)"));
    check = new QPushButton(tr("Check Score (Alt+&c)"));

    p1ip = new QLabel(tr("Player1 IP address: "));
    p2ip = new QLabel(tr("Player2 IP address: "));
    p1port = new QLabel(tr("Port1: "));
    p2port = new QLabel(tr("Port2: "));
    host = new QLabel(tr("Host"));


    player1IP = new QLineEdit;
    player2IP = new QLineEdit;
    player1Port = new QLineEdit;
    player2Port = new QLineEdit;
    hostIP = new QLineEdit;
    hostIP->setText(myIP.getFullAddress()); //alternate: QString::fromStdString(ipAddress)

    QPalette pal;
    pal.setColor(QPalette::Text,QColor(0,0,0));
    player1IP->setMaxLength(25);
    player1IP->setFixedWidth(250);
    player1IP->setAlignment(Qt::AlignLeft);
    player1IP->setReadOnly(false);
    player1IP->setPalette(pal);

    player2IP->setMaxLength(25);
    player2IP->setFixedWidth(250);
    player2IP->setAlignment(Qt::AlignLeft);
    player2IP->setReadOnly(false);
    player2IP->setPalette(pal);

    player1Port->setMaxLength(25);
    player1Port->setFixedWidth(250);
    player1Port->setAlignment(Qt::AlignLeft);
    player1Port->setReadOnly(false);
    player1Port->setPalette(pal);

    player2Port->setMaxLength(25);
    player2Port->setFixedWidth(250);
    player2Port->setAlignment(Qt::AlignLeft);
    player2Port->setReadOnly(false);
    player2Port->setPalette(pal);

    hostIP->setMaxLength(25);
    hostIP->setFixedWidth(250);
    hostIP->setAlignment(Qt::AlignLeft);
    hostIP->setReadOnly(true);
    hostIP->setPalette(pal);

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
    userLayout->addLayout(hostLayout);

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
    ipLayout->addLayout(hostIPLayout);

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
    qDebug()<<"login.login: constructing login class complete.";
}

login::~login()
{
    delete mainLayout;  delete invite;      delete exit;        delete check;
    delete p1ip;        delete p2ip;        delete p1port;      delete p2port;
    delete host;        delete player1IP;   delete player2IP;   delete player1Port;
    delete player2Port; delete hostIP;      delete p1Layout;    delete p2Layout;
    delete hostLayout;  delete port1Layout; delete port2Layout; delete p1IPLayout;
    delete p2IPLayout;  delete p1PortLayout;delete p2PortLayout;delete hostIPLayout;
    delete editorLayout;delete buttonLayout;delete ipLayout;    delete portLayout;
    delete userLayout;  delete userPortlayout;
}

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

    emit emitInvite(p1IP, p2IP, p1Port, p2Port);
    qDebug() << "GUI.Login: Login is sending: " << p1IP << p2IP << p1Port << p2Port <<endl;
}

void login::setMyIP(IP myIP)
{
    qDebug()<<"login.setMyIP: setting my IP Address "<< myIP.getFullAddress()<<" to login window";
    this->myIP = myIP;
    this->hostIP->setText(myIP.getFullAddress());
    this->setWindowTitle(myIP.getFullAddress()+tr(": Starting a new 3P4GO..."));
}

