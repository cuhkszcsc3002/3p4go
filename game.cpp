#include "game.h"




int Game::getMyIndex() const
{
    return myIndex;
}

void Game::setMyIndex(int value)
{
    myIndex = value;
}

bool Game::setIP(IP newIP, int index)
{
    if (index<0 || index> 2) return false;
    else {
        players[index] = newIP;
    }
}

IP Game::getIP(int index)
{
    Q_ASSERT(index>=0 && index<=2);
    return players[index];
}

bool Game::getAvailableFlag() const
{
    return availableFlag;
}

void Game::setAvailableFlag(bool value)
{
    availableFlag = value;
}

int Game::getNewmoveSig() const
{
    return newmoveSig;
}

void Game::setNewmoveSig(int value)
{
    newmoveSig = value;
}

int Game::getSendSigTimes() const
{
    return sendSigTimes;
}

void Game::setSendSigTimes(int value)
{
    sendSigTimes = value;
}

int Game::getBroadcastTimes() const
{
    return broadcastTimes;
}

void Game::setBroadcastTimes(int value)
{
    broadcastTimes = value;
}

int Game::getRestartF() const
{
    return restartF;
}

void Game::setRestartF(int value)
{
    restartF = value;
}

Game::~Game()
{
    delete gui; delete server; delete client;
}



void Game::init()
{
    qDebug() << "Game.init: game initialize started.";

    myPort.show();
    QObject::connect(&myPort, SIGNAL(emitPort(int)), this, SLOT(init2(int)));
}

void Game::init2(int port)
{
    this->Port = port;
    qDebug() << "Game.getPort: receive user enter port: " << port << endl;

    myIndex = -1;
    setAvailableFlag(1);

    players.append(IP());
    players.append(IP());
    players.append(IP());

    QString localIP = Client::getLocalIPAddress();
    Q_ASSERT(localIP != NULL);

    myIP.setAddressFromString(localIP);
    myIP.setPort(Port);
    QList<Key2> keys = RSA2::generateKey();
    myIP.setPublicKey(keys.at(0));
    myIP.setPrivateKey(keys.at(1));

    /* Initialization of the child class: GUI, Client, Server */
    server = new Server;
    client = new Client;
    gui = new GUI;

    client->init(this);
    gui->init(this);

    server->init(this, port);

    loginShow();
    qDebug() << "Game.init2: game initialization succeed.";
}


void Game::restart() //same as init
{
    myIndex = -1;
    setAvailableFlag(1);
    players.append(IP());
    players.append(IP());
    players.append(IP());
    QString localIP = Client::getLocalIPAddress();
    Q_ASSERT(localIP != NULL);
    myIP.setAddressFromString(localIP);
//    myIP.setPort(Server::getPort());
    QList<Key2> keys = RSA2::generateKey();
    myIP.setPublicKey(keys.at(0));
    myIP.setPrivateKey(keys.at(1));

    delete server;
    delete client;
    delete gui;
    server = new Server;
    client = new Client;
    gui = new GUI;
    gui->init(this);

    //   server->init(this);

    client->init(this);
}

void Game::exit()
{

}

void Game::loginShow()
{
    // 1. Invoke gui.loginShow()
    // Note for GUI: Now, 2 options for the player:
    // 1. Wait for the server->receiveInvite
    // 2. When the player invites 2 other players, call sendInvite.
    gui->loginShow();

}

void Game::sendInvite(QString p1IP, QString p2IP, QString p1Port, QString p2Port)
{
    qDebug() << "Game.sendInvite: Receive from login: " << p1IP << p2IP << p1Port << p2Port <<endl;
    gui->transferShow();
    setAvailableFlag(0);

    /* Storing guest player address information */
    players[0] = myIP;
    IP player1, player2;
    player1.setAddressFromString(p1IP);
    player1.setPort(p1Port.toInt());
    player2.setAddressFromString(p2IP);
    player2.setPort(p2Port.toInt());
    players[1] = player1;
    players[2] = player2;
    qDebug() << "Game.sendInvite: all IP are: " << players[0] << players[1] << players[2] << endl;

    /* Sending invite to guest players */
    int result = client->sendInvite(1);
    if (result == 1){
        result = client->sendInvite(2);
        if (result == 1){
            inviteAccepted();//success
        }else{      // Add :  when result = -1, wait please!
            inviteRejected();
        }
    }else{
        inviteRejected();
    }
}

/* I think this method need a signal from client to trigger */
void Game::receiveInvite(IP host_Ip, HttpResponse &response)
{
    receiveInviteRes = &response;
    gui->receiveInvite();
    //change gui signal? store host_IP in players[0]?
}

// TO DO: need to store "response" into receiveInviteRes!
void Game::acceptInvite()
{
    HttpResponse &response = *receiveInviteRes;
    setAvailableFlag(0);
    server->replyInvite(response, 1);
}

void Game::rejectInvite()
{
    HttpResponse &response = *receiveInviteRes;
    server->replyInvite(response, 0);
}


/* For the host*/
void Game::inviteAccepted()
{
    qDebug()<<"Both Guests accept Host's invite.";
    if (check3P() == true){
        int count = 0;
        while(client->sendPlayerInfo() == 0)
        {
            /* need to sleep and try again or rollback when too many fails*/
        }
        startGame();
    }
    /* Might need to deal with false case */
}

/* player1 accepted, while player2 not, or both reject*/
void Game::inviteRejected()
{
    qDebug()<<endl<<"Game.inviteRejected: Host's invite was rejected..";
    setAvailableFlag(1);
    gui->transferClose();
    gui->showReject();
}

bool Game::check3P()
{
    if (players.count() == 3)
    {
        return true;
    }
    else
    {
        return false;
    }
}

///* for other players */

void Game::updatePlayerInfo(IP host, IP B_player, IP C_player)
{
    players[0] = host;
    players[1] = B_player;
    players[2] = C_player;
    for (int i = 0; i < 3; i++)
    {
        if (players[i] == myIP){
            myIndex = i;
            players[i] = myIP;
            break;
        }//如果没有找到 how
    }
    startGame();
}

void Game::startGame()
{
    gui->loginClose();
    gui->transferClose();
    gui->showGame(myIndex);
}

void Game::newclick(MoveChain localMoveChain)       //rules?!
{
    this->localMoveChain = localMoveChain;
    if (myIndex + 1 <= 2)
    {
        if (client->sendForSig(localMoveChain, myIndex+1) == false)
            sigRejected();
    }
    else
    {
        if (client->sendForSig(localMoveChain, 0) == false)
            sigRejected();
    }
}

void Game::validateForSig(MoveChain newMoveChain, int lastSigIndex, HttpResponse & response)
{
    Key2 publicKey = players[myIndex - 1].getPublicKey();
    if (newMoveChain.checkLastSign(publicKey, lastSigIndex)){
        acceptForSig(newMoveChain, response);
    }else{
        rejectForSig(newMoveChain, response);
    }
}

void Game::acceptForSig(MoveChain newMoveChain, HttpResponse &response)
{
    /* If I am the first player right after the movel */
    if ((3+myIndex-newMoveChain.moveList[newMoveChain.length()-1].getPlayerIndex())%3 == 1)
    {
        QString absStr = newMoveChain.abstract();
        QString newSign = RSA2::generateSign(absStr, myIP.getPrivateKey());

        /* If the signature is successfully appended */
        if(newMoveChain.signLast(newSign))
        {
            /* Send the new signature to the next player for check */
            if(myIndex+1 <= 2)
            {
                if (client->sendForSig(newMoveChain, myIndex+1))
                {
                    /* Return the new signature back to the privious movel if I get the respond from next player */
                    server->acceptSig(response);
                }
            }
            else
            {
                if (client->sendForSig(newMoveChain, 0))
                {
                    /* Return the new signature back to the privious movel if I get the respond from next player */
                    server->acceptSig(response);
                }
            }
        }
        else
            qDebug()<<"Append Signature Fail! "<<endl;
    }
    /* If I am the second player right after the movel */
    else if ((3+myIndex-newMoveChain.moveList[newMoveChain.length()-1].getPlayerIndex())%3 == 2)
    {
        QString absStr = newMoveChain.abstract();
        QString newSign = RSA2::generateSign(absStr, myIP.getPrivateKey());

        if(newMoveChain.signLast(newSign))
        {
            /* Return the new signature back to the privious movel */
            server->acceptSig(response);
            /* Send the new signature to the next player for check */
            /* TO DO might need to wait for a wile*/
//            QTimer timer;
//            timer.
            if(myIndex+1 <= 2)
                client->sendForSig(newMoveChain, myIndex+1);
            else
                client->sendForSig(newMoveChain, 0);
        }
        else
            qDebug()<<"Append Signature Fail! "<<endl;
    }
    /* If I am the third player (back to myself) right after the movel */
    else if ((3+myIndex-newMoveChain.moveList[newMoveChain.length()-1].getPlayerIndex())%3 == 0)
    {
            /* Return the new signature back to the privious movel */
            server->acceptSig(response);
            /* Since the signature go back to movel itself and nothing is wrong, hence the movel can broadcast now */
            /* TO DO might need to wait for a wile*/
//            QTimer timer;
//            timer.
            broadcastNewmove();
    }
}



void Game::rejectForSig(MoveChain newMoveChain, HttpResponse &response)
{
    /* If I am the first player right after the movel */
    if ((3+myIndex-newMoveChain.moveList[newMoveChain.length()-1].getPlayerIndex())%3 == 1)
    {
        server->rejectSig(response);
    }
    /* If I am the second player right after the movel */
    else if ((3+myIndex-newMoveChain.moveList[newMoveChain.length()-1].getPlayerIndex())%3 == 2)
    {
        server->rejectSig(response);
    }
    /* If I am the third player (back to myself) right after the movel */
    else if ((3+myIndex-newMoveChain.moveList[newMoveChain.length()-1].getPlayerIndex())%3 == 2)
    {
        server->rejectSig(response);
    }

}

MoveChain Game::sigAccepted()//
{

}

MoveChain Game::sigRejected()
{

}

void Game::broadcastNewmove()
{
    if (client->broadcastNewMove() == false)
    {

        //TO DO: if other don't accept your moveChain, you need to broadcast again
    }

}

  /* For the others */

bool Game::checkNewmove(MoveChain newMoveChain, HttpResponse &response)
{
    if ((this->localMoveChain <= newMoveChain) && (localMoveChain.verifyNewMove(newMoveChain.moveList[newMoveChain.length()-1])))
    {
        acceptNewmove(newMoveChain, response);
    }else{
        rejectNewmove(response);
    }
}

void Game::acceptNewmove(MoveChain newMoveChain, HttpResponse &response)
{
    server->acceptNewMove(response);
    updateNewmove(newMoveChain);
}

void Game::rejectNewmove(HttpResponse &response)
{
    server->acceptNewMove(response);
}

void Game::updateNewmove(MoveChain newMoveChain)
{
    this->localMoveChain = newMoveChain;
}

bool Game::checkFinish()
{
    if (this->localMoveChain.checkLastWin() == true)
    {
        finish();
    }
}

void Game::finish()
{
    gui->gameFinish();
    server->finish();
    client->finish();
    history();
}

void Game::history()
{

}



