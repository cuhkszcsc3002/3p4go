#include "movechain.h"

MoveChain::MoveChain()
{

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

bool MoveChain::validateNewMove(Move newMove)
{
    // 1. Check the playerIndex.
    // 2. Check whether the grid is occupied.
}


QJsonArray MoveChain::toJson()
{
    QJsonArray jsonArray;
    for (Move m: moveList)
    {
        jsonArray.append(QJsonValue(m.toJson()));
    }
    return jsonArray;
}
