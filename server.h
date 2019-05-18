#ifndef SERVER_H
#define SERVER_H

#include <QtCore>
#include <QtNetwork/QtNetwork>
#include <QString>
#include "ip.h"
#include <QCoreApplication>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QString>
#include <QTextStream>
#include "httplistener.h"
#include "httprequesthandler.h"
#include "requestmapper.h"
#include "movechain.h"

class Game;

class Server: public QObject
{
    Q_OBJECT


    /*
     * The pointer of the object game will be stored in the private datafield.
     * The game is an intermediate pathway to connect with other components.
     */

    Game * game;

public:


    /*
     * method: Server
     * The constructor of the Server object.
     * -------------------------------------
     * Usage: Server client;
     */

    Server();


    /*
     * Method: init
     * The initializer of the Server
     * Note: the constructor will be called in the constructor of game,
     * but init will be called in the init of the game, which will be called
     * not only in the first round, but also in the restart.
     * ---------------------------------------------------------------------
     * Usage: client.init(&game);
     */

    void init(Game*);


    /*
     * Method: run
     * Once the game is initialized, start to run local server.
     * ----------------------------------------------------------
     * Usage: server.run();
     */

    void run();


    /*
     * Method: receiveInvite
     * Receive invite from client. The method will not return the response before the invite
     * is allowed.
     * -------------------------------------------------------------------
     * Usage: server.receivite();
     */

    int receiveInvite();

    int replyInvite();


    /*
     * Method: receivePlayerInfo
     * Receive the player's information from client and pass the information to game class.
     * ---------------------------------------------------------------------------------------
     * Usage: int status = client.boardcastNewMove
     */

    QString receivePlayerInfo();


    /*
     * Method: receiveSigReq
     * Receive the signature request from client and pass to game for validation.
     * ---------------------------------------------------------------------------------------
     * Usage: int status = client.boardcastNewMove
     */

    MoveChain receiveSigReq();


    /*
     * Method: rejectSig
     * Receive the request from client. If the signature is invalid, pass the reject info
     * to game class.
     * ---------------------------------------------------------------------------------------
     * Usage: int status = client.boardcastNewMove
     */

    int rejectSig();


    /*
     * Method: acceptSig
     * Receive the request from client. If the signature is valid, pass the accept info
     * to game class.
     * ---------------------------------------------------------------------------------------
     * Usage: int status = client.boardcastNewMove
     */

    int acceptSig();


    /*
     * Method: receiveNewMove
     * Receive the move instruction from game after validated by Game.
     * ---------------------------------------------------------------------------------------
     * Usage: int status = client.boardcastNewMove
     */

    QString receiveNewMove();

//    TODO
    int acceptNewMove();

//    TODO
    int rejectNewMove();


    /*
     * Method: finish
     * The client will be finished when one game is finished. Called by Game.finish().
     * -------------------------------------------------------------------------------
     * Usage: server.finish();
     */


    void finish();
};

void testServer(QCoreApplication&);

#endif // SERVER_H
