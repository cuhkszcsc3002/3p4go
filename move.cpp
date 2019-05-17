#include "move.h"

void Move::setPlayerIndex(int value)
{
    playerIndex = value;
}

void Move::setX(int value)
{
    x = value;
}

void Move::setY(int value)
{
    y = value;
}

bool Move::operator ==(const Move &m) const
{
    return (playerIndex==m.playerIndex && x==m.x && y==m.y);
}

bool Move::fullCmp(const Move &m) const
{
    if (*this == m)
    {
        return signatures==m.signatures;
    }
    else {
        return false;
    }
}

QList<QString> Move::getSignatures() const
{
    return signatures;
}

void Move::setSignatures(const QList<QString> &value)
{
    signatures = value;
}

Move::Move(int playerIndex, int x, int y)
{
    this->playerIndex = playerIndex;
    this->x = x;
    this->y = y;
}

Move::Move(const QJsonObject & obj)
{
    playerIndex = obj.value("playerIndex").toInt();
    x = obj.value("x").toInt();
    y = obj.value("y").toInt();
    QJsonArray array = obj.value("signatures").toArray();
    for (auto i : array) {
        signatures.append(i.toString());
    }
}

bool Move::addSign(const QString & newSign, int index)
{
    if (signatures.length()==index)
    {
        signatures.append(newSign);
        return true;
    }
    else {
        return false;
    }
}

bool Move::overwriteSign(const QString & newSign, int index)
{
    if (signatures.length() <= index)
    {
        return false;
    }
    else {
        signatures[index] = newSign;
        return true;
    }
}

int Move::getPlayerIndex() const
{
    return playerIndex;
}

QList<int> Move::getGrid() const
{
    QList<int> list;
    list.append(x);
    list.append(y);
    return list;
}

int Move::getX() const
{
    return x;
}

int Move::getY() const
{
    return y;
}

QJsonObject Move::toJson()
{
    QJsonObject jsonObj
    {
        {"playerIndex", playerIndex},
        {"x", x},
        {"y", y},
        {"signatures", QJsonArray::fromStringList(signatures)}
    };

    return jsonObj;
}


void testMove()
{
    Move m = Move(0, 1, 2);
    qDebug() << m.getPlayerIndex() << " " << m.getX() << " " << m.getY() << " " << m.toJson();
}
