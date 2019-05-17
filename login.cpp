#include "login.h"
#include <winsock2.h>
//#include <QtWidgets>
//#include <QString>
//#include <string>

/*/
void GetLocalIP(char *ip)
{
    WSADATA wsaData;                                        //initialize WSA
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret == 0)
    {
        char hostname[256];                                 //get mainframe name
        ret = gethostname(hostname, sizeof(hostname));
        if (ret != SOCKET_ERROR)
        {
            HOSTENT* host = gethostbyname(hostname);        //get mainframe ip
            if (host != nullptr)
                strcpy(ip, inet_ntoa(*(in_addr*)*host->h_addr_list));   //return the result
        }
    }
}
/*/

//void GetLocalIP(char* ip)
char* getLocalIP(void)
{
    WSADATA wsaDataqq;
    PHOSTENT hostinfo;
    in_addr dest;

    WSAStartup(MAKEWORD(1,1), &wsaDataqq);
    char name[256];
    char *ipAddr= new char[16];

    if(gethostname(name, sizeof(name)) == SOCKET_ERROR || (hostinfo = gethostbyname(name)) == nullptr)
        return nullptr;
    else
    {
        for(int a = 0; hostinfo->h_addr_list[a] != nullptr; a++)                    //multiple wangka, can get multiple ip iterately
        {
            memcpy(&dest, hostinfo->h_addr_list[a], hostinfo->h_length);
            if (a==1)
                ipAddr=inet_ntoa(dest);
        }
        WSACleanup();
        return ipAddr;
    }
}



login::login(QWidget *parent) : QWidget (parent)
{
    //ipAddress = "";
    ip = new char[16];
    //GetLocalIP(ip);
    ip = getLocalIP();
    ipAddress = ip;

    this->resize(QSize(600,400));

    invite = new QPushButton(tr("Start 3P4GO (Alt+&s)"));
    exit = new QPushButton(tr("Exit (Alt+&e)"));
    check = new QPushButton(tr("Check Score (Alt+&c)"));

    p1 = new QLabel(tr("Player 1"));
    p2 = new QLabel(tr("Player 2"));
    host = new QLabel(tr("Host"));


    player1IP = new QLineEdit(tr("Enter P1 IP address..."));
    player2IP = new QLineEdit(tr("Enter P2 IP address..."));
    hostIP = new QLineEdit();
    hostIP->setText(QString::fromStdString(ipAddress));

    player1IP->setMaxLength(25);
    player1IP->setAlignment(Qt::AlignLeft);
    player1IP->setFixedWidth(250);

    player2IP->setMaxLength(25);
    player2IP->setAlignment(Qt::AlignLeft);
    player2IP->setFixedWidth(250);

    hostIP->setMaxLength(25);
    hostIP->setAlignment(Qt::AlignLeft);
    hostIP->setFixedWidth(250);
    hostIP->setReadOnly(true);

    p1Layout = new QHBoxLayout;
    p2Layout = new QHBoxLayout;
    hostLayout = new QHBoxLayout;

    p1IPLayout = new QHBoxLayout;
    p2IPLayout = new QHBoxLayout;
    hostIPLayout = new QHBoxLayout;

    editorLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;

    ipLayout = new QVBoxLayout;
    userLayout = new QVBoxLayout;
    mainLayout = new QVBoxLayout;

    p1Layout->addStretch();
    p1Layout->addWidget(p1);
    p1Layout->addStretch();
    p2Layout->addStretch();
    p2Layout->addWidget(p2);
    p2Layout->addStretch();
    hostLayout->addStretch();
    hostLayout->addWidget(host);
    hostLayout->addStretch();
    userLayout->addLayout(p1Layout);
    userLayout->addLayout(p2Layout);
    userLayout->addLayout(hostLayout);

    p1IPLayout->addWidget(player1IP);
    p1IPLayout->addStretch();
    p2IPLayout->addWidget(player2IP);
    p2IPLayout->addStretch();
    hostIPLayout->addWidget(hostIP);
    hostIPLayout->addStretch();
    ipLayout->addLayout(p1IPLayout);
    ipLayout->addLayout(p2IPLayout);
    ipLayout->addLayout(hostIPLayout);

    editorLayout->addLayout(userLayout);
    editorLayout->addLayout(ipLayout);

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
    QString P1 = player1IP->text();
    QString P2 = player2IP->text();

    std::string P1ip = P1.toStdString();
    std::string P2ip = P2.toStdString();


    //this->hide();
    emit showTransfer();
}

void login::startReceived()
{
    this->hide();
}

