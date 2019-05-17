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

class Game;

class GUI : public QWidget
{
    Q_OBJECT

/* Private section:
 * ---------------------------------
 * Declaration of all Widget Windows
 */
private:
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

    GUI(QWidget *parent = nullptr);
    ~GUI();

    void init(Game*);
    void loginShow();
    void receiveInvite();
    void showReject();
    void showGame();
    void newClicked();  //not complete yet
    void updateNewMovel();  //not complete yet
    void gameFinish();
    void takeCount();
};

#endif // GAME_INIT_H
