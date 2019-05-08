#include "game.h"

MoveChain::MoveChain()
{

}

MoveChain::MoveChain(QString jsonString)
{
    QJsonDocument json = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonArray array = json.array();
    for (QJsonValue v:array) {

       moveList.append(Move(v.toObject()));
    }
}

int MoveChain::nextPlayer()
{
    if (moveList.length()==0)
    {
        return 0;
    }
    else {
        return (moveList.last().getPlayerIndex()+1) % 3;
    }
}

bool MoveChain::verifyNewMove(Move newMove)
{
    if (moveList.isEmpty()) return true;

    // 1. Check the playerIndex.

    if (nextPlayer() != newMove.getPlayerIndex())
    {
        qDebug() << "PlayerIndex Wrong!" << nextPlayer() << newMove.getPlayerIndex();
        return false;
    }

    // 2. Check whether the grid is occupied.
    for (Move m : moveList)
    {
//        qDebug() << m.getX() << newMove.getX() << m.getY() << newMove.getY();
        if (m.getX() == newMove.getX() && m.getY() == newMove.getY())
        {
            return false;
        }
    }
    return true;
}

bool MoveChain::newMove(Move newMove)
{
    if (verifyNewMove(newMove))
    {
        moveList.append(newMove);
        return true;
    }
    else {
        return false;
    }

}

int MoveChain::checkWin()
{
    if (moveList.length()<9) return -1;
    for (int i=3*3; i<=moveList.length(); i++)
    {
        QList<Move> testChain = moveList.mid(0, i);
        qDebug() << i ;
        if (checkLastWin(testChain)) return (i+2)%3;
    }
    return -1;
}

bool MoveChain::checkLastWin()
{
    return checkLastWin(moveList);
}

bool MoveChain::checkLastWin(QList<Move> & testMoveChain)
{
    Move last = testMoveChain.back();
    // directions store the 7-bit lines of 4 directions.
    bool directions[4][WINNUM*2-1] = {{false}};
    int checkDirectionIndex = -1;

    for (int i=0; i<4; i++) {
        directions[i][WINNUM-1] = true;
    }

    for (Move & m:testMoveChain) {
        if (m == last)
        {
            return false;
        }
        if (m.getPlayerIndex() != last.getPlayerIndex()) continue;
        else {
            int xDiff = last.getX() - m.getX();
            int yDiff = last.getY() - m.getY();
            if (abs(xDiff)>=WINNUM || abs(yDiff)>=WINNUM)
            {
                checkDirectionIndex = -1;
                continue;
            }
            else {
                if (xDiff == 0)
                {
                    directions[0][yDiff+WINNUM-1] = true;
                    checkDirectionIndex = 0;
                }
                else if (xDiff==yDiff)
                {
                    directions[1][xDiff+WINNUM-1] = true;
                    checkDirectionIndex = 1;
                }
                else if (yDiff == 0)
                {
                    directions[2][xDiff+WINNUM-1] = true;
                    checkDirectionIndex = 2;
                }
                else if (xDiff == -yDiff)
                {
                    directions[3][xDiff+WINNUM-1] = true;
                    checkDirectionIndex = 3;
                }
                else {
                    checkDirectionIndex = -1;
                    continue;
                }

                // For debug
                for (int i=0; i<4; i++)
                {
                    for (int j = 0; j < 2*WINNUM-1; ++j) {
                        std::cout << directions[i][j] << ' ';
                    }
                    std::cout << std::endl;
                }
                std::cout << std::endl;

                // Check the corresponding direction.
                int left, right;
                for (left=WINNUM-1; left>=0; left--) {
                    if (!directions[checkDirectionIndex][left]) break;
                }
                for (right=WINNUM-1; right<=WINNUM*2; right++) {
                    if (!directions[checkDirectionIndex][right]) break;
                }
                if (right - left >= WINNUM-1) return true;
            }
        }
    }
    return false;
}

bool MoveChain::signLast(QString newSign, int index, bool forceSign)
{
    // 1. Get the signature from the Game.
    // 2. Check if the index number is correct.
    // 3. Sign.

    return moveList.last().addSign(newSign, index);
}

bool MoveChain::checkLastSign(Key2 publicKey, int index)
{
    if (index>=moveList.last().getSignatures().length()) {
        qDebug() << "CheckLastSign: index overflow.";
        return false;
    }

    QString sign = moveList.last().getSignatures()[index];
    return RSA2::verify(abstract(), sign, publicKey);
}

bool MoveChain::checkLastSign(Key2 publicKey)
{
    return checkLastSign(publicKey, moveList.last().getSignatures().length()-1);
}


QJsonArray MoveChain::toJson()
{
    QJsonArray jsonArray;
    for (Move m: moveList)
    {
        jsonArray.append(QJsonValue(m.toJson()));
        qDebug()<<m.toJson();
    }
    return jsonArray;
}

QString MoveChain::toJsonString()
{
    QJsonDocument doc;
    doc.setArray(toJson());
    return QString(doc.toJson());
}

QString MoveChain::abstract()
{
    QString absStr;
    for (Move& m: moveList)
    {
        absStr += QString::number(m.getX()) + QString::number(m.getY()) + QString::number(m.getPlayerIndex());
    }
    absStr = absStr.mid(0, ENCODELEN);
    return absStr;
}

bool MoveChain::operator<=(MoveChain &mc) const
{
    QList<Move> mc1, mc2;
    if (moveList.length()==mc.moveList.length())
    {
        mc1 = moveList.mid(0, moveList.length()-1);
        mc2 = mc.moveList.mid(0, mc.moveList.length()-1);
    }
    else if (moveList.length() == mc.moveList.length()-1) {
        mc1 = moveList;
        mc2 = mc.moveList.mid(0, mc.moveList.length()-1);
    }
    else {
        return false;
    }
    for (int i=0; i<mc1.length(); i++) {
        if (!mc1[i].fullCmp(mc2[i])) return false;
    }
    return true;
}

MoveChain MoveChain::jsonToMoveChain(QString jsonString)
{
    QJsonDocument json = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonArray array = json.array();
    MoveChain newMoveChain;
    for (QJsonValue v:array) {

       newMoveChain.moveList.append(Move(v.toObject()));
    }
    return newMoveChain;
}


void testMoveChain()
{
    MoveChain mc;
    QList<int> move = {0, 0, 0};
    qDebug() << mc.newMove(Move(move[0], move[1], move[2]));
    qDebug() << mc.signLast("123456", 0);
    move = {1, 0, 1};
    qDebug() << mc.newMove(Move(move[0], move[1], move[2]));
    move = {2, 0, 2};
    qDebug() << mc.newMove(Move(move[0], move[1], move[2]));
    move = {0, 1, 0};
    qDebug() << mc.newMove(Move(move[0], move[1], move[2]));
    move = {1, 0, 10};
    qDebug() << mc.newMove(Move(move[0], move[1], move[2]));
    move = {2, 0, 11};
    qDebug() << mc.newMove(Move(move[0], move[1], move[2]));
    move = {0, 2, 0};
    qDebug() << mc.newMove(Move(move[0], move[1], move[2]));
    move = {1, 2, 10};
    qDebug() << mc.newMove(Move(move[0], move[1], move[2]));
    move = {2, 2, 20};
    qDebug() << mc.newMove(Move(move[0], move[1], move[2]));
    qDebug() << "check win:" << mc.checkLastWin();
    qDebug() << "The winner is" << mc.checkWin();
    move = {0, 3, 0};
    qDebug() << mc.newMove(Move(move[0], move[1], move[2]));
    qDebug() << "check win:" << mc.checkLastWin();
    qDebug() << "The winner is" << mc.checkWin();

    QString jsonString = mc.toJsonString();
    qDebug() << jsonString;
    MoveChain newMoveChain(jsonString);
    qDebug() << newMoveChain.toJsonString();
//    move = {1, 2, 30};
//    qDebug() << mc.newMove(Move(move[0], move[1], move[2]));
//    move = {2, 2, 40};
//    qDebug() << mc.newMove(Move(move[0], move[1], move[2]));
//    move = {0, 4, 0};
//    qDebug()<< mc.newMove(Move(move[0], move[1], move[2]));

//    qDebug()<<mc.toJsonString();

}
