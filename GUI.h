#ifndef GAME_INIT_H
#define GAME_INIT_H

#include <QtWidgets>
#include "chessboard.h"
#include "invite.h"
#include "login.h"
#include "score.h"
#include "transfer.h"
#include "reject.h"
#include "finish.h"
#include "timer.h"
#include "port.h"
#include "httpresponse.h"

class Game;

class GUI : public QObject
{
    Q_OBJECT

/* Private section:
 * ---------------------------------
 * Declaration of all Widget Windows
 */
public:
    login *log;
    score *scor;
    transfer *trans;
    reject *rej;
    inviteReceive *invite;
    finish *fini;
    chessBoard *chess;
//    timer *counter;

private slots:
    //void restartReceive();

public:

//    GUI(QWidget *parent = nullptr);
    GUI();
    ~GUI();

    void init(Game*);
    void loginShow(IP myIP);
    void loginClose();
    void receiveInvite(const QString &, stefanfrings::HttpResponse &response);
    void showReject();
    void showGame(int myIndex);
    void newClicked();  //not complete yet
    void updateNewMovel(MoveChain localMoveChain);  //not complete yet
    void gameFinish();
    void takeCount();
    void transferShow();
    void transferClose();

    inviteReceive *getInvite() const;
    void setInvite(inviteReceive *value);
};

#endif // GAME_INIT_H
