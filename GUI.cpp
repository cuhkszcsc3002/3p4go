/*/
#include <QApplication>
#include "chessboard.h"
#include "invitereceive.h"
#include "item.h"
#include "login.h"
#include "score.h"
#include "transfer.h"
/*/
#include "game.h"

GUI::GUI(QWidget *parent) : QWidget (parent){}

GUI::~GUI(){}


void GUI::init(Game *sgame)
{
    log = new login;
    scor = new score;
    trans = new transfer;
    rej = new reject;
    invite = new inviteReceive;
    fini = new finish;
    chess = new chessBoard;

    /* Connect GUI's subclasses */
    QObject::connect(log, SIGNAL(showScore()), scor, SLOT(checkReceived()));
    QObject::connect(log, SIGNAL(showTransfer()), trans, SLOT(receiveInvite()));
    QObject::connect(trans, SIGNAL(comfirmReceived()), log, SLOT(startReceived()));

    /* Connecting GUI class and its subclass to GAME class */
    QObject::connect(log, SIGNAL(emitInvite(QString, QString, QString, QString)), sgame, SLOT(sendInvite(QString, QString, QString, QString)));
    QObject::connect(invite, SIGNAL(inviteAccept()), sgame, SLOT(acceptInvite()));
    QObject::connect(invite, SIGNAL(inviteReject()), sgame, SLOT(rejectInvite()));
    QObject::connect(chess, SIGNAL(pushMoveChain(MoveChain)), sgame, SLOT(newclick(MoveChain)));
    qDebug() << "GUI init finish";
}

//void GUI::restartReceive(){
//    this->init();
//}

void GUI::loginShow(){
    log->show();
}

void GUI::receiveInvite(){
    invite->show();
}

void GUI::showReject(){
    rej->show();
}

void GUI::showGame(int myIndex){
    chess->setMyIndex(myIndex);
    chess->show();
}

void GUI::newClicked(){

}

void GUI::updateNewMovel(MoveChain localMoveChain){
    chess->pullMoveChain(localMoveChain);
    chess->update();
}

void GUI::gameFinish(){
    fini->show();
}

//void GUI::takeCount(){
//    counter = new timer;
//    counter->show();
//}
