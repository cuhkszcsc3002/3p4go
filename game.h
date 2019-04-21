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
#include <iostream>
#include <string>
#include <QDebug>
#include "newmove.h"
using namespace std;


class Game
{
    /*
     * Game.availableFlag stores the state of the player.
     * Note: 1 represents that the player is available
     * to be invited, while 0 represents that the player
     * has been invited by another host.
     */

    bool availableFlag;

    /*
     * Game.nextPlayer stores the IP of the next player.
     * Note: the next player will give a new movement
     * after you have done a newmove.
     */

    string nextPlayer;

    /*
     * Game.lastPlayer stores the IP of the last player.
     * Note: the last player will give a new movement
     * after the next player has taken a new movement.
     * Order: You -> the next player -> the last player -> You
     */

    string lastPlayer;


public:
    Game();

    /*
     * Method: constructor
     * Usage: Game game(player);
     * --------------------------------------
     * This method initialize 3 parameters
     */

    void loginShow();

    /*
     * Method: LoginShow
     * Usage:
     * ---------------------------------------
     * This method is called when the game is
     * to be opened. It calls Gui.loginShow() and
     * Server.run() respectively.
     */

    void sendInvite(string players_Ip);

    /*
     * Method: sendInvite
     * Usage:
     * -----------------------------------
     * This method is called when the host
     * inviting other players through IP at GUI.
     * It calls Client.sendInvite() respectively.
     */

    void receiveInvite(string host_Ip);

    /*
     * Method: receiveInvite
     * Usage:
     * ------------------------------------------------
     * This method is called by Server.receiveInvite(),
     * when the users is invited by the host.
     * It calls GUI.receiveInvite() and change the GUI signal.
     */

    void acceptInvite();

    /*
     * Method: acceptInvite
     * Usage: Game::acceptInvite()
     * ---------------------------------------------------------
     * This method is triggered by signal rejectInvite in invite.h.
     * It change "availableFlag" from 1 to 0, so that other hosts
     * can not invite him again and he can not invite others as a host.
     * It also calls Server.replyInvite(), to inform the host.
     */

    void rejectInvite();

    /*
     * Method: rejectInvite
     * Usage:
     * ---------------------------------------
     * This method is triggered by signal rejectInvite in invite.h.
     * It represents that the player reject the invite from the host.
     * It also calls Server.replyInvite(), to inform the host.
     */
    
    /* For the host*/
    void inviteAccept();
    
    /*
     * Method: inviteAccept
     * Usage:
     * ---------------------------------------
     * This method is called when a player has
     * accepted the invite from the host.
     * It will store the IP of the player, and
     * call GUI.showMessage().
     */

    void rejectAccept();

    /*
     * Method: rejectAccept
     * Usage:
     * ---------------------------------------
     * This method is called when a player has
     * rejected the invite from the host.
     * It will call GUI.showMessage(), and
     * let the host invite other players instead.
     */

    bool check3P();

    /*
     * Method: check3P
     * ---------------------------------------
     * This method is called to confirm that the
     * host and other two players are ready for the
     * game. By checking the acceptInvite signals
     * of other players that the host invited,
     * the client.sendPlayerInfo() is called if
     * it returns 1. At last, it will call
     * Game.startGame().
     */

    /* for other players */

    void updatePlayerInfo(string host, string B_player, string C_player);

    /*
     * Method: updatePlayerInfo
     * ---------------------------------------
     * This method is called by Server.receivelayerInfo()
     * It will recognize the IP string of itself between
     * B_player and C_player, then store the IP of the other
     * player in order. At last, it will call Game.startGame().
     */

    /* for all */

    void startGame();

    /*
     * Method: startGame
     * ---------------------------------------
     * This method is called by Game.check3P()
     * and Game.updatePlayerInfo().
     * It calls GUI.showGame().
     */

    /*
     * Method: checkFinish
     * ---------------------------------------
     * This method is called after
     * and Game.updatePlayerInfo().
     * It calls GUI.showGame().
     */

    bool checkFinish();

    /*
     * Method:
     * ---------------------------------------
     * This method is called by Game.check3P()
     * and Game.updatePlayerInfo().
     * It calls GUI.showGame().
     */


    void finish();

    int history();

    void exit();


};

#endif // GAME_H





/*
ostream & operator<<(ostream & os, GameModel & rhs);
string ReverseColor(string color);
Player ReversePlayer(Player player);
*/

