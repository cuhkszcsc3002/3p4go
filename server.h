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

//#include "game.h"


class Game;

class Server: public QObject
{
    Q_OBJECT


    /*
     * The pointer of the object game will be stored in the private datafield.
     * The game is an intermediate pathway to connect with other components.
     */

    Game * game;
    QCoreApplication * serverApp;

signals:

    void receiveForSigFinish();

    void receiveNewMoveFinish();

    void receivePlayerInfoFinish();

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

    void init(Game*,int avaliablePort);


    /*
     * Method: run
     * Once the game is initialized, start to run local server.
     * ----------------------------------------------------------
     * Usage: server.run();
     */

    void run(int avaliablePort);


    /*
     * Method: replyInvite
     * After game response to the invite (accept or reject), get the result and pass it to client.
     * -------------------------------------------------------------------
     * Usage: server.receivite();
     */

    int replyInvite(HttpResponse * response,int result);


    /*
     * Method: rejectSig
     * Receive the request from client. If the signature is invalid, pass the reject info
     * to game class.
     * ---------------------------------------------------------------------------------------
     * Usage: int status = client.boardcastNewMove
     */

    void rejectSig(HttpResponse & response);


    /*
     * Method: acceptSig
     * Receive the request from client. If the signature is valid, pass the accept info
     * to game class.
     * ---------------------------------------------------------------------------------------
     * Usage: int status = client.boardcastNewMove
     */

    void acceptSig(HttpResponse & response);


    /*
     * Method: acceptNewMove
     * Return the accept response to client.
     * ---------------------------------------------------------------------------------------
     * Usage: void acceptNewMove(response);
     */

    void acceptNewMove(HttpResponse & response);


    /*
     * Method: rejectNewMove
     * Return the accept response to client.
     * ---------------------------------------------------------------------------------------
     * Usage: void rejectNewMove(response);
     */

    void rejectNewMove(HttpResponse & response);


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
