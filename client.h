/*
 * Class Client
 * Client class includes essential methods for making specific HTTP requests
 * with other 2 players.
 *
 * Generally, the return value is an int:
 * 1: success
 * 0: rejected (if a reject status is needed)
 * -1: connection fails
 *
 * The private data field includes a pointer of the game object, which is the main
 * source of game information.
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore>
#include <QtNetwork/QtNetwork>
#include <QString>
#include "ip.h"
#include "rsa2.h"

class Game;

class Client: public QObject
{
    Q_OBJECT


    /*
     * The pointer of the object game will be stored in the private datafield.
     * The game is an intermediate pathway to connect with other components.
     */

    Game* game;

public:


    /*
     * method: Client
     * The constructor of the Client object.
     * -------------------------------------
     * Usage: Client client;
     */

    Client();

    QString postRequest(QString url, QJsonDocument data);


    /*
     * Method: getLocalIPAddress
     * This function will return the user's local IP.
     * If no IP available, return NULL.
     * ----------------------------------------------
     * Usage: QString localIP = getLocalIPString();
     */

    static QString getLocalIPAddress();

    /*
     * Method: getLocalIP
     * This function will return the user's local IP.
     * Then it will run the RSA to generate a key pair.
     * If no IP available, return NULL.
     * ----------------------------------------------
     * Usage: IP localIP = getLocalIP();
     */

    static IP getLocalIP();


    /*
     * Method: init
     * The initializer of the Client.
     * Note: the constructor will be called in the constructor of game,
     * but init will be called in the init of the game, which will be called
     * not only in the first round, but also in the restart.
     * ---------------------------------------------------------------------
     * Usage: client.init(&game);
     */

    void init(Game*);


    /*
     * Method: sendInvite
     * Send an invite request to a corresponding IP address:port,
     * with predefined codes for invitation.
     * Return 1 if success; return 0 if rejected; return -1 if connection fails.
     * ----------------------------------------------------------
     * Usage: client.sendInvite(IPindex);
     *
     * ------------------------------
     * POST FORMAT:
     * A JSON object.
     * IP: XXX.XXX.XXX.XXX
     * port: XXXX
     *
     * EXPECTED FEEDBACK:
     * A JSON object.
     * result: 1 / 0
     * key: key.encode()
     */

    int sendInvite(int playerIndex);


    /*
     * Method: sendPlayerInfo
     * Send players' information to all other players, and start the game.
     * Return 1 if success; return -1 if connection fails.
     * -------------------------------------------------------------------
     * Usage: client.sendPlayerInfo();
     *
     * -------------------------------
     * POST FORMAT:
     * A JSON ARRAY.
     * [{IP: ...; port: ...; key: key.encode()}, { ... }, { ... }]
     *
     * EXPECTED FEEDBACK:
     * 1: Successfully Received.
     * 0: Something Wrong, may try to send again.
     */

    int sendPlayerInfo();


    /*
     * Method: sendForSig
     * Send the whole history chain and the signiture chain to the next player for signature.
     * Return 1 if success; return 0 if rejected; return -1 if connection fails.
     * --------------------------------------------------------------------------------------
     * Usage: int status = client.sendForSig();
     *
     * ----------------------------------------
     * POST FORMAT:
     * A JSON OBJECT.
     * { moveChain: moveChain.toJsonString() }
     *
     * SERVER's WORK:
     * 1. decode moveChainString
     * 2. Send to game.
     *
     *
     * EXCEPPTED FEEDBACK:
     * 1. I accept, sign, and send to the next player, while the next player also replies 1.
     * 0. I reject, or the next player rejects.
     */

    int sendForSig();


    /*
     * Method: boardcastNewMove
     * Boardcast the whole history chain as well as the signiture chain to other 2 players.
     * Boardcast will be conducted when 3 signatures for the current move have been collected.
     * Return 1 if success; return 0 if rejected; return -1 if connect fails.
     * ---------------------------------------------------------------------------------------
     * Usage: int status = client.boardcastNewMove
     *
     * -------------------------------------------
     * POST FORMAT:
     * A JSON OBJECT.
     * { moveChain: moveChain.toJsonString() }
     *
     * EXPECTED FEEDBACK:
     * 1. Accepted.
     * 0. Rejected.
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


void testClient();

#endif // CLIENT_H
