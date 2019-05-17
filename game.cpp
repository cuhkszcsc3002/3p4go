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

void Game::init()
{
    myIndex = -1;
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
    gui->init();

    //   server.init(this);

    client.init(this);
}

void Game::restart() //same as init
{
    myIndex = -1;
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

void Game::sendInvite(IP players_Ip, int p)
{
    client.sendInvite(players_Ip);

}

void Game::receiveInvite(IP host_Ip)
{
    gui->receiveInvite();
    //change gui signal?
}

void Game::acceptInvite()
{
    setAvailableFlag(0);
    server.replyInvite(IP myIp, IP host_Ip);
}

void Game::rejectInvite()
{
    server.replyInvite(IP myIp, IP host_Ip);
}

/* For the host*/

void Game::inviteAccepted(IP players_Ip, int p, Qlist players)
{
    players.append(players_Ip);
    gui->showReject();
    if (check3P() == true){
        client.sendPlayerInfo();
        game.startGame();
    }
}

void Game::inviteRejected(IP players_Ip, int p)
{
    gui->showReject();
}

bool Game::check3P()
{
    if (players.count() == 3){
        return true;
    }
    else{
        return false;
    }
}

/* for other players */

void Game::updatePlayerInfo(IP host, IP B_player, IP C_player)
{
    players[0] = host;
    players[1] = B_player;
    players[2] = C_player;
    for (int i = 0; i < 3; i++){
        if (players[i].getAddress() == myIP.getAddress() && players[i].getPort() == myIP.getPort()){
            myIndex = i;
            players[i] = myIP;
            break;
        }//如果没有找到 how
    }
}

void Game::startGame()
{
    gui->showGame();
}

void Game::newclick()
{

}

bool Game::validateForSig()
{

}

void Game::acceptForSig()
{

}

void Game::rejectForSig()
{

}

MoveChain Game::sigAccepted()
{

}

MoveChain Game::sigRejected(IP ones_IP)
{

}

bool Game::collectAllSig()
{

}

void Game::broadcastNewmove(MoveChain newMoveChain)
{

}

  /* For the others */

bool Game::checkNewmove(MoveChain newMoveChain)
{

}

void Game::acceptNewmove()
{

}

void Game::rejectNewmove()
{

}

MoveChain Game::updateNewmove(MoveChain newMoveChain)
{

}

bool Game::checkFinish()
{

}

void Game::finish()
{

}

void Game::history()
{

}




