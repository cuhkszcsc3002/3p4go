#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <QRectF>
#include <QPainter>
#include <QColor>
#include <QEvent>
#include <QPoint>
#include <QMessageBox>
#include <QMouseEvent>
//#include "chessboard.h"
#include "game.h"

using namespace std;

chessBoard::chessBoard(QWidget *parent) : QWidget(parent)
{
    qDebug()<<"chessboard.chessbaord: initializing chessboard class";
    isJump = false;
    this->resize(1050, 990);            //set the size of the window

    /* Initialization of some parameters of the chessbaord:
     * Firstly, the cursor is initionally at (500 pix, 500 pix) of the screen (physical) and correspondingly, the
     * cursor is at (0, 0) of the chessboard (logical)
     * Secondly, the left boundary of the chessboard initially represents the x=-9 axis, but for convenience, I still
     * use QPoint stucture to store the information. Correspondingly, right boundary initially represents the x=9 axis,
     * up boundary initially represents the y=-9 axis, down boundary initially represents the y=9 axis.
     */
    phyLocation = new QPoint(INIT_POSX, INIT_POSY);
    logLocation = new QPoint(0, 0);

    leftBoundAxis = new QPoint(-9, 0);
    rightBoundAxis = new QPoint(9, 0);
    upBoundAxis = new QPoint(0, -9);
    downBoundAxis = new QPoint(0, 9);

    /*Setting the background of the chessboard */
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#B1723C"));
    this->setPalette(palette);
    setMouseTracking(true);
    qDebug()<<"chessboard.chessboard: chessboard class initialization completed";
}

chessBoard::~chessBoard()
{
    delete phyLocation;     delete logLocation; delete leftBoundAxis;
    delete rightBoundAxis;  delete upBoundAxis; delete downBoundAxis;
}


void chessBoard::paintEvent(QPaintEvent *e)
{
//    qDebug() << "Paint Event Start";
    DrawChessboard();		//draw chess board
    DrawItems();			//draw chess stone

    drawLocatorWithKeyboard();  //draw the locator
    update();
}


void chessBoard::DrawChessboard()
{
//    qDebug() << "DrawChessboard Start";
    /* Set and draw the boundary lines, chesboard lines, samll balack points and
     * background of the chessboard*/
    QPainter painter(this);             //construct base of the chessboard
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    QPen pen = painter.pen();           //set the color of chessboard boundary
    pen.setColor(QColor("#8D5822"));
    pen.setWidth(7);
    painter.setPen(pen);

    QBrush brush;                       //set the background colcor of the chessboard
    brush.setColor(QColor("#EEC085"));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);            //draw the chessboard background color
    painter.drawRect(35, 35, 932, 932); //draw the boundary of the chess board


    pen.setColor(Qt::black);            //set the colot of the lines
    pen.setWidth(1);
    painter.setPen(pen);
    for (int i=0; i<19; i++)            //draw lines of the chessboard, 19 lines in total
    {
        painter.drawLine(50 + i*50, 50, 50 + i*50, 950);
        painter.drawLine(50, 50 + i*50, 950, 50 + i*50);
    }

    /* Draw the five balck points on the chessboard */
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.drawRect(245, 245, 10, 10); //left up corner
    painter.drawRect(745, 245, 10, 10); //right up corner
    painter.drawRect(245, 745, 10, 10); //left down corner
    painter.drawRect(745, 745, 10, 10); //right down corner
    painter.drawRect(495, 495, 10, 10); //middle corner


    /* Set and print the coordinate indicators of the X axis and Y axis */
    QRect textVertical, textHorizontal1, textHorizontal2, textHorizontal3, textHorizontal4, textHorizontal5, textHorizontal6,
            textHorizontal7, textHorizontal8, textHorizontal9, textHorizontal10, textHorizontal11, textHorizontal12,
            textHorizontal13, textHorizontal14, textHorizontal15, textHorizontal16, textHorizontal17, textHorizontal18,
            textHorizontal19;
    QString verticalAxis, horizontalAxis1, horizontalAxis2, horizontalAxis3, horizontalAxis4, horizontalAxis5, horizontalAxis6,
            horizontalAxis7, horizontalAxis8, horizontalAxis9, horizontalAxis10, horizontalAxis11, horizontalAxis12,
            horizontalAxis13, horizontalAxis14, horizontalAxis15, horizontalAxis16, horizontalAxis17, horizontalAxis18,
            horizontalAxis19;

    textVertical.setRect(980, 42, 60, 950); textHorizontal1.setRect(45, 970, 30, 20); textHorizontal2.setRect(95, 970, 30, 20);
    textHorizontal3.setRect(145, 970, 30, 20); textHorizontal4.setRect(195, 970, 30, 20); textHorizontal5.setRect(245, 970, 30, 20);
    textHorizontal6.setRect(295, 970, 30, 20); textHorizontal7.setRect(345, 970, 30, 20); textHorizontal8.setRect(395, 970, 30, 20);
    textHorizontal9.setRect(445, 970, 30, 20); textHorizontal10.setRect(495, 970, 30, 20); textHorizontal11.setRect(545, 970, 30, 20);
    textHorizontal12.setRect(595, 970, 30, 20); textHorizontal13.setRect(645, 970, 30, 20); textHorizontal14.setRect(695, 970, 30, 20);
    textHorizontal15.setRect(745, 970, 30, 20); textHorizontal16.setRect(795, 970, 30, 20); textHorizontal17.setRect(845, 970, 30, 20);
    textHorizontal18.setRect(895, 970, 30, 20); textHorizontal19.setRect(945, 970, 30, 20);
    verticalAxis.sprintf("%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n%d \n\n\n%d "
                         "\n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d \n\n\n%d",
                         upBoundAxis->y()+0, upBoundAxis->y()+1, upBoundAxis->y()+2, upBoundAxis->y()+3, upBoundAxis->y()+4,
                         upBoundAxis->y()+5, upBoundAxis->y()+6, upBoundAxis->y()+7, upBoundAxis->y()+8, upBoundAxis->y()+9,
                         upBoundAxis->y()+10, upBoundAxis->y()+11, upBoundAxis->y()+12, upBoundAxis->y()+13, upBoundAxis->y()+14,
                         upBoundAxis->y()+15, upBoundAxis->y()+16, upBoundAxis->y()+17, upBoundAxis->y()+18);

    horizontalAxis1.sprintf("%d", leftBoundAxis->x()+0); horizontalAxis2.sprintf("%d", leftBoundAxis->x()+1);
    horizontalAxis3.sprintf("%d", leftBoundAxis->x()+2); horizontalAxis4.sprintf("%d", leftBoundAxis->x()+3);
    horizontalAxis5.sprintf("%d", leftBoundAxis->x()+4); horizontalAxis6.sprintf("%d", leftBoundAxis->x()+5);
    horizontalAxis7.sprintf("%d", leftBoundAxis->x()+6); horizontalAxis8.sprintf("%d", leftBoundAxis->x()+7);
    horizontalAxis9.sprintf("%d", leftBoundAxis->x()+8); horizontalAxis10.sprintf("%d", leftBoundAxis->x()+9);
    horizontalAxis11.sprintf("%d", leftBoundAxis->x()+10); horizontalAxis12.sprintf("%d", leftBoundAxis->x()+11);
    horizontalAxis13.sprintf("%d", leftBoundAxis->x()+12); horizontalAxis14.sprintf("%d", leftBoundAxis->x()+13);
    horizontalAxis15.sprintf("%d", leftBoundAxis->x()+14); horizontalAxis16.sprintf("%d", leftBoundAxis->x()+15);
    horizontalAxis17.sprintf("%d", leftBoundAxis->x()+16); horizontalAxis18.sprintf("%d", leftBoundAxis->x()+17);
    horizontalAxis19.sprintf("%d", leftBoundAxis->x()+18);


    painter.drawText(textVertical, Qt::AlignTop, verticalAxis, nullptr);
    painter.drawText(textHorizontal1, Qt::AlignTop, horizontalAxis1, nullptr);
    painter.drawText(textHorizontal2, Qt::AlignTop, horizontalAxis2, nullptr);
    painter.drawText(textHorizontal3, Qt::AlignTop, horizontalAxis3, nullptr);
    painter.drawText(textHorizontal4, Qt::AlignTop, horizontalAxis4, nullptr);
    painter.drawText(textHorizontal5, Qt::AlignTop, horizontalAxis5, nullptr);
    painter.drawText(textHorizontal6, Qt::AlignTop, horizontalAxis6, nullptr);
    painter.drawText(textHorizontal7, Qt::AlignTop, horizontalAxis7, nullptr);
    painter.drawText(textHorizontal8, Qt::AlignTop, horizontalAxis8, nullptr);
    painter.drawText(textHorizontal9, Qt::AlignTop, horizontalAxis9, nullptr);
    painter.drawText(textHorizontal10, Qt::AlignTop, horizontalAxis10, nullptr);
    painter.drawText(textHorizontal11, Qt::AlignTop, horizontalAxis11, nullptr);
    painter.drawText(textHorizontal12, Qt::AlignTop, horizontalAxis12, nullptr);
    painter.drawText(textHorizontal13, Qt::AlignTop, horizontalAxis13, nullptr);
    painter.drawText(textHorizontal14, Qt::AlignTop, horizontalAxis14, nullptr);
    painter.drawText(textHorizontal15, Qt::AlignTop, horizontalAxis15, nullptr);
    painter.drawText(textHorizontal16, Qt::AlignTop, horizontalAxis16, nullptr);
    painter.drawText(textHorizontal17, Qt::AlignTop, horizontalAxis17, nullptr);
    painter.drawText(textHorizontal18, Qt::AlignTop, horizontalAxis18, nullptr);
    painter.drawText(textHorizontal19, Qt::AlignTop, horizontalAxis19, nullptr);
//    qDebug() << "DrawChessboard Finished";
}


void chessBoard::DrawItems()
{
//    qDebug() << "DrawItem Start";
    /* Set the pen that draw chess stones */
    QPainter painter(this);
    QPen pen = painter.pen();
    pen.setColor(Qt::transparent);
    painter.setPen(pen);

    /* Scan all chess stones */
    for (int i=0; i<localMoveChain.length(); i++)
    {
        /* Reading from the string and get the chess stone information */
        int x = localMoveChain.moveList[i].getX(); //atoi(strX.c_str());
        int y = localMoveChain.moveList[i].getY(); //atoi(strY.c_str());
        int player = localMoveChain.moveList[i].getPlayerIndex(); //atoi(strPlay.c_str());

        /* Draw the chess stones if it is within the chessboard */
        if( leftBoundAxis->x() <= x && x <= rightBoundAxis->x() && upBoundAxis->y() <= y && y <= downBoundAxis->y())
        {
            switch (player)
            {
            case 0 :
                painter.setBrush(Qt::red);
                break;
            case 1 :
                painter.setBrush(Qt::yellow);
                break;
            case 2 :
                painter.setBrush(Qt::blue);
                break;
            default:
                break;
            }
            drawStoneAtPoint(painter, x, y);
        }
        //cout<<"x: "<<x<<" y: "<<y<<" Player:"<<strPlay<<endl;
    }
}


void chessBoard::drawStoneAtPoint(QPainter& painter, int logX, int logY)
{
    int phyX = 50 + abs(leftBoundAxis->x()-logX)*50;
    int phyY = 50 + abs(upBoundAxis->y()-logY)*50;
    //cout<<"x: "<<phyX<<" y: "<<phyY<<endl;
    QPoint ptCenter(phyX, phyY);
    painter.drawEllipse(phyX-25, phyY-25, 50, 50);
}

void chessBoard::jumpToNewMove()
{
/* These codes are the junping mechanism, do once when receive new move from other player */
    int lastMove = this->localMoveChain.length()-1;
//        qDebug() << "MoveChain lastmove: "<< lastMove;
    if (lastMove>0)
    {
        int x = this->localMoveChain.moveList[lastMove].getX(); //atoi(strX.c_str());
        int y = this->localMoveChain.moveList[lastMove].getY(); //atoi(strY.c_str());
        this->leftBoundAxis->setX(x-9);
        this->rightBoundAxis->setX(x+9);
        this->upBoundAxis->setY(y-9);
        this->downBoundAxis->setY(y+9);
        this->logLocation->setX(x);
        this->logLocation->setY(y);
        this->phyLocation->setX(INIT_POSX);
        this->phyLocation->setY(INIT_POSY);
        update();


//        noteNewMove();
//            cout<<"end player x: "<<x<<" y: "<<y<<endl;
    }
}

/* Draw a indicate simbol on the new move chess stone */
void chessBoard::noteNewMove()
{
    QPainter painter(this);
    QPen pen = painter.pen();
    pen.setColor(Qt::transparent);
    painter.setPen(pen);
    painter.setBrush(Qt::white);
    painter.drawRect(495, 495, 10, 10);
}


void chessBoard::drawLocatorWithKeyboard()
{
    QPainter painter(this);
    QPen pen = painter.pen();

    pen.setColor(Qt::red);
    pen.setWidth(3);
    painter.setPen(pen);

    painter.drawLine(phyLocation->x()-25, phyLocation->y()-25, phyLocation->x()-10, phyLocation->y()-25);
    painter.drawLine(phyLocation->x()+10, phyLocation->y()-25, phyLocation->x()+25, phyLocation->y()-25);
    painter.drawLine(phyLocation->x()+25, phyLocation->y()-25, phyLocation->x()+25, phyLocation->y()-10);
    painter.drawLine(phyLocation->x()+25, phyLocation->y()+10, phyLocation->x()+25, phyLocation->y()+25);
    painter.drawLine(phyLocation->x()+10, phyLocation->y()+25, phyLocation->x()+25, phyLocation->y()+25);
    painter.drawLine(phyLocation->x()-25, phyLocation->y()+25, phyLocation->x()-10, phyLocation->y()+25);
    painter.drawLine(phyLocation->x()-25, phyLocation->y()+25, phyLocation->x()-25, phyLocation->y()+10);
    painter.drawLine(phyLocation->x()-25, phyLocation->y()-10, phyLocation->x()-25, phyLocation->y()-25);

    QString msg;
    QString index = "Player" + QString::number(myIndex) + ": ";
    msg.sprintf("physical locator: %d, %d. logical locator: %d, %d.  left:%d, right:%d, up:%d, down:%d",
                phyLocation->x(), phyLocation->y(), logLocation->x(), logLocation->y(),
                leftBoundAxis->x(), rightBoundAxis->x(), upBoundAxis->y(), downBoundAxis->y());
    index = index + msg;
    setWindowTitle(index);
}


/*
 * Implementation notes: keyPressEvent()
 * -----------------------------------------------------------------------------------------------
 * This function allow user control the cursor by using keyboard. Keyboard hit "w" will
 * make the cursor move up, "s" will make it move down, "a" will make it move left and "d"
 * will make it move right. Noted that the cursor will not move forward as it reach to one
 * of the boundaries of the chessboard.
 */
void chessBoard::keyPressEvent(QKeyEvent *event)
{
    /* Dealing with the case that player press "A" key */
    if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
    {
        logLocation->setX(logLocation->x() - 1);
        if(phyLocation->x() > 50)
            phyLocation->setX(phyLocation->x() - 50);
        else if (phyLocation->x() == 50)
        {
            leftBoundAxis->setX(leftBoundAxis->x()-1);
            rightBoundAxis->setX(rightBoundAxis->x()-1);
        }

    }
    /* Dealing with the case that player press "B" key */
    else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
    {
        logLocation->setX(logLocation->x() + 1);
        if(phyLocation->x() < 950)
            phyLocation->setX(phyLocation->x() + 50);
        else if (phyLocation->x() == 950)
        {
            leftBoundAxis->setX(leftBoundAxis->x()+1);
            rightBoundAxis->setX(rightBoundAxis->x()+1);
        }
    }
    /* Dealing with the case that player press "W" key */
    else if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
    {
        logLocation->setY(logLocation->y() - 1);
        if(phyLocation->y() > 50)
            phyLocation->setY(phyLocation->y() - 50);
        else if (phyLocation->y() == 50)
        {
            upBoundAxis->setY(upBoundAxis->y()-1);
            downBoundAxis->setY(downBoundAxis->y()-1);
        }
    }
    /* Dealing with the case that player press "S" key */
    else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
    {
        logLocation->setY(logLocation->y() + 1);
        if(phyLocation->y() < 950)
            phyLocation->setY(phyLocation->y() + 50);
        else if (phyLocation->y() == 950)
        {
            upBoundAxis->setY(upBoundAxis->y()+1);
            downBoundAxis->setY(downBoundAxis->y()+1);
        }
    }
    /* Dealing with the case that user press "ENTER" key */
    else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        Move newMove(myIndex, logLocation->x(), logLocation->y());
        qDebug() << "ENTER" << newMove.getGrid();

        /* Check if is player's turn */
        if(localMoveChain.length()%3 == myIndex)
        {
            /* Check if player's location had been occupied */
            if(localMoveChain.verifyNewMove(newMove) == true)
            {
                localMoveChain.newMove(newMove);
                emit pushMoveChain(localMoveChain);
            }
            else
                std::cout<<"New move error!"<<endl;
        }
        else
            std::cout<<"Not your turn!!!"<<endl;

        /*need to check with network*/
        isJump = false;
     }
}

void chessBoard::pullMoveChain(MoveChain localMoveChain)
{
    this->localMoveChain = localMoveChain;
    jumpToNewMove();
}

void chessBoard::setMyIndex(int myIndex)
{
    this->myIndex = myIndex;
}

