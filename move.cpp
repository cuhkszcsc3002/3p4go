#include "move.h"

Move::Move(int playerIndex, int x, int y)
{
    this->playerIndex = playerIndex;
    this->x = x;
    this->y = y;
}

int Move::getPlayerIndex()
{
    return playerIndex;
}

QList<int> Move::getGrid()
{
    QList<int> list;
    list.append(x);
    list.append(y);
    return list;
}

int Move::getX()
{
    return x;
}

int Move::getY()
{
    return y;
}

QJsonObject Move::toJson()
{
    QJsonObject jsonObj
    {
        {"playerIndex", playerIndex},
        {"x", x},
        {"y", y}
    };

    return jsonObj;
}


void testMove()
{
    Move m = Move(0, 1, 2);
    qDebug() << m.getPlayerIndex() << " " << m.getX() << " " << m.getY() << " " << m.toJson();
}
