/*
 * Class Game
 * Game class includes essential methods for game logic, such as checking new move,
 * judging winner, storing go-pieces' coordinates, and storing players' history scores.
 * The private data field includes a pointer of the game object, which is the main
 * source of game information.
 */

#ifndef GAME_H
#define GAME_H

#include <QtCore>
#include <QtNetwork/QtNetwork>
#include <QString>
#include <QList>
#include <QObject>
#include <iostream>
#include <string>
#include <QDebug>
#include "ip.h"
#include "coordinate.h"
#include "movechain.h"
#include "client.h"
#include "server.h"
#include "GUI.h"
//#include "port.h"


using namespace std;

class Game : public QObject
{
    Q_OBJECT
public:
    friend class Client;
    friend class Server;
    friend class GUI;
    friend class HttpRequestHandler;
//    friend class port;

    Client *client;
    Server *server;
    GUI *gui;
    QApplication * app;
    port myPort;

    int Port;

    /*
     * Game.availableFlag stores the state of the player.
     * Note: 1 represents that the player is available
     * to be invited, while 0 represents that the player
     * has been invited by another host.
     */

    bool availableFlag;


    /*
     * There are 3 players in order in this game.
     * The first player is the host, but not necessarily the
     * current player! Information about the index of the current
     * player is stored in myIndex.
     */

    QList<IP> players;


    /*
     * This is myIP, containing the address, privateKey, and the publicKey.
     */

    IP myIP;

    /*
     * myIndex: the index of the current player, which is 0, 1, or 2.
     * Before game starts, myIndex = -1.
     * myIP = players[myIndex];可以删去availableFlag了
     */

    int myIndex;


//    /*
//     * Game.nextPlayer stores the IP of the next player.
//     * Note: the next player will give a new movement
//     * after you have done a newmove.
//     */

//    IP nextPlayer;

//    /*
//     * Game.lastPlayer stores the IP of the last player.
//     * Note: the last player will give a new movement
//     * after the next player has taken a new movement.
//     * Order: You -> the next player -> the last player -> You
//     */

//    IP lastPlayer;

    HttpResponse * receiveInviteRes;

    /*
     * Game.newmoveSig stores the signature state of a newmove.
     * Note:
     * 1 represents the signatures of newmove in the movechain
     * are right, and it will trigger Game.acceptForSig().
     * 0 represents there is something wrong with the signatures of
     * newmove in the movechain, and it will trigger Game.rejectForSig().
     * It will turn back to 0 in Game.updateNewmove().
     * Order: You -> the next player -> the last player -> You
     */

    int newmoveSig;

    /*
     * Game.sendSigTimes stores how many times did the player send
     * history chain to others and be rejected.
     * Note: 0 represents the movechain has not passed to the player.
     * 1 represents the history movechain has been sent to the next player.
     * if the movechain is rejected (Game.SigRejected() is called) by next player,
     * sendSigTimes will plus 1 and the player will delete his signature and
     * send a movechain with his new signned signature.
     * If sendSIgTimes is 4, it will alarm.
     */

    int sendSigTimes = 0;

    /*Client加了一个client->updateNewmove(ones'IP) to inform 另外两个players update the chain.
     * Game.broadcastTimes represents the state of broadcastNewmove().
     * If one player returns True through client->broadcastNewmove(),
     * the signal will plus 1. If one player returns false, the player will
     * send the history chain again to others and the signal will be
     * changed back to 0. If the signal equals to 2, Game.updateNewmove and
     * client->updateNewmove(ones'IP) will be called.
     */

    int broadcastTimes = 0;

    /*
     * Game.restartF is to trigger Game.restart().
     * if it becomes 1, a new game will start.
     */

    int restartF = 0;


    /*
     * Game.localMoveChain is used to store current movechain.
     */

    MoveChain localMoveChain;

public:
    Game(QApplication * a)
    {app = a;
        QObject::connect(this, SIGNAL(emitStartGame()), this, SLOT(startGame()));
    }
    ~Game();

    /*
     * Method: constructor
     * Usage: Game game(player);
     * --------------------------------------
     * This method initialize 3 parameters
     */


    /*
     * Method: init
     * The initializer of the Game.
     * Note: the constructor will call the constructors of GUI, Server, client->
     * It will be called not only in the first round, but also in the restart.
     * ---------------------------------------------------------------------
     * Usage: ;
     */

    void init();


    /*
     * The set, get methods.
     */
    int getMyIndex() const;
    void setMyIndex(int value);
    bool getAvailableFlag() const;
    void setAvailableFlag(bool value);
    int getNewmoveSig() const;
    void setNewmoveSig(int value);
    int getSendSigTimes() const;
    void setSendSigTimes(int value);
    int getBroadcastTimes() const;
    void setBroadcastTimes(int value);
    int getRestartF() const;
    void setRestartF(int value);

    bool setIP(IP newIP, int index);
    IP getIP(int index);

    /*
     * Set, get methods end.
     */



    /*
     * Method: LoginShow
     * Usage:
     * ---------------------------------------
     * This method is called when the game is
     * to be opened. It calls Gui.loginShow() and
     * Server.run() respectively.
     */

    void loginShow();

    /*
     * Method: receiveInvite
     * Usage:
     * ------------------------------------------------
     * This method is called by Server.receiveInvite(),
     * when the users is invited by the host.
     * It calls GUI.receiveInvite() and change the GUI signal.
     */
    void receiveInvite(IP host_Ip, HttpResponse &response);

    /* For the host*/


    /*
     * Method: inviteAccepted
     * Usage:
     * ---------------------------------------
     * This method is called when a player has
     * accepted the invite from the host.
     * It will store the IP of the player, and
     * call check3p以及startgame连起来了
     */

    void inviteAccepted(int count);

    /*
     * Method: inviteRejected
     * Usage:
     * ---------------------------------------
     * This method is called when a player has
     * rejected the invite from the host.
     * It will call GUI.showMessage(), and
     * call Game.sendInvite(IP otherPlayers_Ip, int p)
     * to invite other players instead.
     */

    void inviteRejected();

    /*
     * Method: check3P
     * ---------------------------------------
     * This method is called to confirm that the
     * host and other two players are ready for the
     * game. By checking the acceptInvite signals
     * of other players that the host invited,
     * the client->sendPlayerInfo() is called if
     * it returns true. At last, it will call
     * Game.startGame().
     */

    bool check3P();



    /* for other players */

    /*
     * Method: updatePlayerInfo
     * ---------------------------------------
     * This method is called by Server.receivelayerInfo()
     * It will recognize the IP string of itself between
     * B_player and C_player, then store the IP of the other
     * player in order. At last, it will call Game.startGame().
     */

    void updatePlayerInfo(const IP &host, const IP &B_player, const IP &C_player);



    /* for all */


    /* for those who are not the owner of a newmove */

    /*
     * Method: validateForSig
     * Usage:
     * ---------------------------------------
     * This method is called by Server.receiveSigReq(),
     * and used to prevent cheating. It will call
     * moveChain.checkLastSign(publicKey,lastSigIndex)
     * to check whether there are differences on the
     * signatures of the newmove until now.
     * It will change the Game.newmoveSig() to trigger
     * other methods.
     */

    void validateForSig(MoveChain newMoveChain, HttpResponse &response);

    /*
     * Method: acceptForSig
     * Usage:
     * ---------------------------------------
     * This method is triggered if Game.newmoveSig
     * is 1, and it will call Server.acceptSig(), to
     * response to the last player and send the
     * history chain with his signature to next player.
     */

    void acceptForSig(MoveChain newMoveChain, HttpResponse &response);

    /*
     * Method: rejectForSig
     * Usage:
     * ---------------------------------------
     * This method is triggered if Game.newmoveSig
     * is 2, and it will call Server.rejectSig(),
     * responsing to the player who send the history
     * chain to him.
     */

    void rejectForSig(MoveChain newMoveChain, HttpResponse &response);



 /* For players who have sent movechain with signatures to others */


    /*
     * Method: sigAccepted
     * Usage:
     * ---------------------------------------
     * This method is called if client->sendForSig() returns 1.
     * the player who send the moveChain will be informed of
     * that the next player has accepted the history chain and
     * signatures. It will save signatures and recover the
     * sendSIgTimes to 0.
     */

    MoveChain sigAccepted();

    /*
     * Method: sigRejected
     * Usage:
     * ---------------------------------------
     * This method is called if client->sendForSig() returns 0.
     * the player will be asked to send a new history chain
     * with correct signatures, and the signal
     * Game.sendSigTimes will plus 1 every time.
     * If Game.sendSigTimes is 4, it will alarm.
     */

    MoveChain sigRejected();


   /* For the one who own the newmove*/

    /*
     * Method: collectAllSig
     * Usage:
     * ----------------------------------------------------
     * This method is called after Game.validateForSig(),
     * and used to check whether they have collected all
     * signatures.
     */

    bool collectAllSig();

    /*
     * Method: broadcastNewmove
     * Usage:
     * -------------------------------------------
     * This method is called by Game.collectAllSig().
     * It will call client->broadcastNewmove() to send
     * the new history movechain to the other two players,
     * and wait for their responses. If one player response
     * false (broadcastTimes = -1), it will send the history
     * moveChain again, or update the new movechain when
     * broadcastTimes equal to 2.
     */

    void broadcastNewmove();

  /* For the others */

    /*
     * Method: checkNewmove
     * Usage:
     * ---------------------------------------
     * This method will check whether there is
     * difference between the movechains and the
     * newmove is valid or not.
     * It is called by Server.receiveNewmove(),
     * and used to call Game.acceptNewmove() or
     * Game.rejectNewmove(). If the newmove is valid
     * (it returns 1), Newmove.acceptNewmove() is called;
     * otherwise, Newmove.rejectNewmove() is called.
     */

    bool checkNewmove(MoveChain newMoveChain, HttpResponse &response);

    /*
     * Method: acceptNewmove
     * Usage:
     * ---------------------------------------
     * This method is called when Newmove.checkNewmove()
     * returns 1, and used to call Server.acceptNewmove().
     */

    void acceptNewmove(MoveChain newMoveChain, HttpResponse &response);

    /*
     * Method: rejectNewmove
     * Usage:
     * ---------------------------------------
     * This method is called when Newmove.checkNewmove()
     * returns 0, and used to call Server.rejectNewmove().
     */

    void rejectNewmove(HttpResponse &response);

    /*
     * Method: updateNewmove
     * Usage:
     * ---------------------------------------
     * This method is called by Newmove.broadcastNewmove()
     * or client->updateMoveChain, and used to update the movechain
     * in localMoveChain and call GUI.updateNewmove().
     * newmoveSig will be changed back to 0.
     */

    void updateNewmove(MoveChain newMoveChain);


    /*
     * Method: checkFinish
     * ---------------------------------------------------
     * This method is called after newmove.updateNewmove(),
     * and used to check whether someone wins. If it returns
     * 1, then Game.finish() will be called.
     */

    void checkFinish();

    /*
     * Method: finish
     * ---------------------------------------------
     * This method is called when Game.checkFinish()
     * returns 1, and it calls GUI.finish().
     * Passing 1 if lose, 2 if draw, 0 if win.
     */

    void finish(int status);

    /*
     * Method: history
     * ---------------------------------------
     * This method is called by Game.finish(),
     * and used to calculate the score for this round
     * and update (read + calculate + write) the score history
     * in history_score.txt.
     */

    void history();

    /*
     * Method: restart
     * ------------------------------------------
     * This Method is called when the signal restartF
     * equals to 1, then a new game will start.
     */

    void restart();


    /*
     * Method: exit
     * ---------------------------------------
     * This method is called when the user choose
     * to exit from the game.
     */

    void exit();

    GUI *getGui() const;
    void setGui(GUI *value);

private slots:
    /*
     * Method: sendInvite
     * Usage:
     * -----------------------------------
     * playerIndex can be 1 or 2, 1 represents the
     * nextPlayer, while 2 represents the lastPlayer.
     * This method is called when the host
     * inviting other players through IP at GUI.
     * It calls client->sendInvite() respectively.
     *
     * ----------------------------------------------------------
     * Called by GUI, when the player pushes the "invite" button.
     *
     * Then, call client->sendInvite(players_IP).
     * Note: DON'T modify players[p]! This will be done by client
     * because client will receive the privateKey.???
     *
     * If the return is true, go to check3P().QQQ问check3P()is called by inviteAccepted()
     * Else, do nothing.
     */
    void sendInvite(QString p1IP, QString p2IP, QString p1Port, QString p2Port);

    /*
     * Method: acceptInvite
     * Usage: Game::acceptInvite()
     * ---------------------------------------------------------
     * This method is triggered by signal acceptInvite in invite.h.
     * It change "availableFlag" from 1 to 0, so that other hosts
     * can not invite him again and he can not invite others as a host.
     * It also calls Server.replyInvite(), to inform the host.
     */
    void acceptInvite();

    /*
     * Method: rejectInvite
     * Usage:
     * ---------------------------------------
     * This method is triggered by signal rejectInvite in invite.h.
     * It represents that the player reject the invite from the host.
     * It also calls Server.replyInvite(), to inform the host.
     */
    void rejectInvite();

    /*
     * Method: newclick
     * Usage:
     * ---------------------------------------
     * This method is triggered by GUI.newclick(),
     * which has checked whether the coordinate
     * is available or not, and Game.newclick() is
     * used to call client->sendForSig().
     */

    void newclick(MoveChain localMoveChain);


    void init2(int port);

    /*
     * Method: startGame
     * ---------------------------------------
     * This method is called by Game.check3P()
     * and Game.updatePlayerInfo().
     * It calls GUI.showGame() and change
     * the signal restartF to 0.
     */

    void startGame();


signals:
    void emitStartGame();



#endif // GAME_H





/*
ostream & operator<<(ostream & os, GameModel & rhs);
string ReverseColor(string color);
Player ReversePlayer(Player player);
*/
};
