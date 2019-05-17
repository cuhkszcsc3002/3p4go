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

Game::Game()
{
    // NOTE: Game::init(); 不要写在这里!单独调用init();
}

Game::~Game()
{

}



void Game::init()
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

    /* Initialization of the child class: GUI, Client, Server */
    gui->init(this);

    //   server.init(this);

    client.init(this);



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

    //    gui.init(this);

    //   server.init(this);

    client.init(this);
}

void Game::exit()
{

}

void Game::loginShow()
{
    // 1. Invoke gui.loginShow()
    // Note for GUI: Now, 2 options for the player:
    // 1. Wait for the server.receiveInvite
    // 2. When the player invites 2 other players, call sendInvite.
    gui->loginShow();
}

void Game::sendInvite(QString p1IP, QString p2IP, QString p1Port, QString p2Port)
{
    setAvailableFlag(0);
    /* Storing guest player address information */
    IP player1, player2;
    player1.setAddressFromString(p1IP);
    player1.setPort(p1Port.toInt());
    player2.setAddressFromString(p2IP);
    player2.setPort(p2Port.toInt());
    players[1] = player1;
    players[2] = player2;

    /* Sending invite to guest players */
    int result = client.sendInvite(1);
    if (result == 1){
        result = client.sendInvite(2);
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
void Game::receiveInvite(IP host_Ip)
{
    gui->receiveInvite();
    //change gui signal?
}

void Game::acceptInvite()
{
    setAvailableFlag(0);
    server.replyInvite(myIp, host_Ip);
}

void Game::rejectInvite()
{
    server.replyInvite(myIp, host_Ip);
}


///* For the host*/

void Game::inviteAccepted()
{
    if (check3P() == true){
        int count = 0;
        while(client.sendPlayerInfo() == 0)
        {
            /* need to sleep and try again or rollback when too many fails*/
        }
        startGame();
    }
    /* Might need to deal with false case */
}

void Game::inviteRejected()
{                   //player1 accepted, while player2 not.
    setAvailableFlag(1);
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
    gui->showGame(myIndex);
}

void Game::newclick(MoveChain localMoveChain)       //rules?!
{
    this->localMoveChain = localMoveChain;
    client.sendForSig();
}

void Game::validateForSig(QString newmovechain)
{
    MoveChain newMoveChain;
    //todo: trans QString newmovechain to  MoveChain newMoveChain
    if (newMoveChain <= localMoveChain){
        setNewmoveSig(1);
    }else{
        setNewmoveSig(0);
    }
}

void Game::acceptForSig()
{
    server.acceptSig();
}

void Game::rejectForSig()
{
    server.rejectSig();
}

//MoveChain Game::sigAccepted()
//{

//}

//MoveChain Game::sigRejected(IP ones_IP)
//{

//}

//bool Game::collectAllSig()
//{

//}

//void Game::broadcastNewmove(MoveChain newMoveChain)
//{

//}

//  /* For the others */

//bool Game::checkNewmove(MoveChain newMoveChain)
//{

//}

//void Game::acceptNewmove()
//{

//}

//void Game::rejectNewmove()
//{

//}

//MoveChain Game::updateNewmove(MoveChain newMoveChain)
//{

//}

//bool Game::checkFinish()
//{

//}

//void Game::finish()
//{

//}

//void Game::history()
//{

//}




