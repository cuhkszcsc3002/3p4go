/*/
#include <QApplication>
#include "chessboard.h"
#include "invitereceive.h"
#include "item.h"
#include "login.h"
#include "score.h"
#include "transfer.h"
/*/
#include "GUI.h"

GUI::GUI(QWidget *parent) : QWidget (parent){}

GUI::~GUI(){}


void GUI::init()
{
    log = new login;
    scor = new score;
    trans = new transfer;
    rej = new reject;
    invite = new inviteReceive;
    fini = new finish;
    chess = new chessBoard;
    counter = new timer;

    QObject::connect(log, SIGNAL(showScore()), scor, SLOT(checkReceived()));
    QObject::connect(log, SIGNAL(showTransfer()), trans, SLOT(receiveInvite()));
    QObject::connect(trans, SIGNAL(comfirmReceived()), chess, SLOT(startReceived()));
    QObject::connect(trans, SIGNAL(comfirmReceived()), log, SLOT(startReceived()));

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

void GUI::showMessage(){
    rej->show();
}

void GUI::showGame(){
    chess->show();
}

void GUI::newClicked(){

}

void GUI::updateNewMovel(){

}

void GUI::gameFinish(){
    fini->show();
}

void GUI::takeCount(){
    counter->show();
}
