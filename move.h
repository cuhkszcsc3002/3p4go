/*
 * Class: Move
 * Move stores information of one move, that is, a specific player
 * places a Go at a specific place.
 */

#ifndef MOVE_H
#define MOVE_H

#include <QList>
#include <QString>
#include <QJsonObject>
#include <QtDebug>

class Move
{
    /*
     * playerIndex
     * The playerIndex for the current player. Its range is from 0 to 2.
     */

    int playerIndex;

    int x;

    int y;

    /*
     * At most 3 signatures for every move.
     */

    QList<QString> signatures;

public:

    /*
     * Constructor
     * Constructor and initializer for the Move object, with the playerIndex, x, and y.
     * --------------------------------------------------------------------------------
     * Usage: Move m = Move(playerIndex, x, y);
     */

    Move(int playerIndex, int x, int y);

    /*
     * Method: addSign
     * Add a new sign to the index.
     * Fail: return 0: when the index is not the next index or >=3.
     * Success: return 1: write the sign and return 1.
     */

    bool addSign(QString newSign, int index);

    int getPlayerIndex();


    /*
     * Method: getGrid
     * Get a size-2 QList for the x, y index.
     * --------------------------------------
     * Usage: QList grid = move.getGrid();
     */

    QList<int> getGrid();


    int getX();


    int getY();


    /*
     * Method: toJson
     * Return the json object of the current move, which can be easily interpretted as a string.
     * -------------------------------------------
     * Usage: QJsonObject jsonObj = move.toJson();
     */

    QJsonObject toJson();

};

void testMove();
#endif // MOVE_H
