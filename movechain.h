/*
 * Class: MoveChain
 * MoveChain stores and maintains a list of moves.
 */

#ifndef MOVECHAIN_H
#define MOVECHAIN_H

#include <QList>
#include <QJsonArray>
#include "move.h"

class MoveChain
{
    QList<Move> moveList;

public:

    /*
     * Constructor
     * Initialize a moveChain object.
     * ------------------------------
     * Usage: MoveChain moveChain;
     */

    MoveChain();


    /*
     * Method: nextPlayer
     * Return the playerIndex of the next player.
     * ------------------------------------------
     * Usage: int id = moveChain.nextPlayer();
     */

    int nextPlayer();


    /*
     * Method: validateNewMove
     * Check whether the new move is validate.
     * ---------------------------------------
     * Usage: bool check = moveChain.validateNewMove();
     */

    bool validateNewMove(Move newMove);


    /*
     * Method: newMove
     * First check if it is valid. Then append it to the moveList.
     * ------------------------------------------------------------
     * Usage: bool check = moveChain.newMove();
     */

    bool newMove(Move NewMove);


    /*
     * Method: checkWin
     * Check whether a specific player wins. If anyone wins, return the playerIndex.
     * If no one wins, return -1.
     * ----------------------------
     * Usage: int winner = moveChain.checkWin();
     */

    int checkWin();


    /*
     * Method: toJson
     * Return the QJsonArray of moveChain.
     * ------------------------------------
     * Usage: QJsonArray jsonArray = moveChain.tojson();
     */

    QJsonArray toJson();
};

#endif // MOVECHAIN_H
