#ifndef SERVER_H
#define SERVER_H

#include <QtCore>
#include <QtNetwork/QtNetwork>
#include <QString>
#include <ip.h>
#include "httplistener.h"
#include "httprequesthandler.h"


class Client: public QObject
{
    Q_OBJECT


    /*
     * The pointer of the object game will be stored in the private datafield.
     * The game is an intermediate pathway to connect with other components.
     */

//    Game * game;

public:


    /*
     * method: Client
     * The constructor of the Client object.
     * -------------------------------------
     * Usage: Client client;
     */

    Client();


    /*
     * Method: init
     * The initializer of the Client.
     * Note: the constructor will be called in the constructor of game,
     * but init will be called in the init of the game, which will be called
     * not only in the first round, but also in the restart.
     * ---------------------------------------------------------------------
     * Usage: client.init(&game);
     */

//    void init(Game*);


    /*
     * Method: sendInvite
     * Send an invite request to a corresponding IP address:port,
     * with predefined codes for invitation.
     * Return 1 if success; return 0 if rejected; return -1 if connection fails.
     * ----------------------------------------------------------
     * Usage: client.sendInvite(ip);
     */

    int sendInvite(IP &ip);


    /*
     * Method: sendPlayerInfo
     * Send players' information to all other players, and start the game.
     * Return 1 if success; return -1 if connection fails.
     * -------------------------------------------------------------------
     * Usage: client.sendPlayerInfo();
     */

    int sendPlayerInfo();


    /*
     * Method: sendForSig
     * Send the whole history chain and the signiture chain to the next player for signature.
     * Return 1 if success; return 0 if rejected; return -1 if connection fails.
     * --------------------------------------------------------------------------------------
     * Usage: int status = client.sendForSig();
     */

    int sendForSig();


    /*
     * Method: boardcastNewMove
     * Boardcast the whole history chain as well as the signiture chain to other 2 players.
     * Boardcast will be conducted when 3 signatures for the current move have been collected.
     * Return 1 if success; return 0 if rejected; return -1 if connect fails.
     * ---------------------------------------------------------------------------------------
     * Usage: int status = client.boardcastNewMove
     */

    int boardcastNewMove();


    /*
     * Method: finish
     * The client will be finished when one game is finished. Called by Game.finish().
     * -------------------------------------------------------------------------------
     * Usage: client.finish();
     */

    void finish();
};


#endif // SERVER_H
