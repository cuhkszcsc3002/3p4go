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

public:

    /*
     * Constructor
     * Constructor and initializer for the Move object, with the playerIndex, x, and y.
     * --------------------------------------------------------------------------------
     * Usage: Move m = Move(playerIndex, x, y);
     */

    Move(int playerIndex, int x, int y);


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
