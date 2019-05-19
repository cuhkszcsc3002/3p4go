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

inviteReceive *GUI::getInvite() const
{
    return invite;
}

void GUI::setInvite(inviteReceive *value)
{
    invite = value;
}

GUI::GUI(QWidget *parent) : QWidget (parent){}

GUI::~GUI(){
    delete log;     delete scor;
    delete trans;   delete rej;
    delete invite;  delete fini;
    delete chess;
}


void GUI::init(Game *sgame)
{
    qDebug() <<endl<< "GUI.init: gui initialization start...";
    log = new login;
    scor = new score;
    trans = new transfer;
    rej = new reject;
    invite = new inviteReceive;
    fini = new finish;
    chess = new chessBoard;

    qDebug() << "GUI.init: signal and slot connection start...";
    /* Connect GUI's subclasses */
    QObject::connect(log, SIGNAL(showScore()), scor, SLOT(checkReceived()));

    /* Connecting GUI class and its subclass to GAME class */
    QObject::connect(log, SIGNAL(emitInvite(QString, QString, QString, QString)), sgame, SLOT(sendInvite(QString, QString, QString, QString)));
    QObject::connect(invite, SIGNAL(inviteAccept()), sgame, SLOT(acceptInvite()));
    QObject::connect(invite, SIGNAL(inviteReject()), sgame, SLOT(rejectInvite()));
    QObject::connect(chess, SIGNAL(pushMoveChain(MoveChain)), sgame, SLOT(newclick(MoveChain)));
    qDebug() << "GUI.init: GUI init finish";
}

void GUI::loginShow(IP myIP){
    log->setMyIP(myIP);
    log->show();
}

void GUI::loginClose(){
    log->close();
}

void GUI::receiveInvite(const QString & ipAddress, HttpResponse & response){
    qDebug() << "GUI.receiveInvite";
    invite->receiveInvite(ipAddress);
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

void GUI::transferShow(){
    trans->show();
}

void GUI::transferClose(){
    trans->close();
}

//void GUI::takeCount(){
//    counter = new timer;
//    counter->show();
//}

