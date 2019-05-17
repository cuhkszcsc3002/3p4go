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
#include <QJsonArray>
#include <QtDebug>
#include "coordinate.h"

// The winner's requirement of consecutive moves(Go).

#define WINNUM 4

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
     * Constructor from QJsonObject
     * ----------------------------
     * Usage: Move m(jsonObj);
     */

    Move(const QJsonObject & obj);


    /*
     * Construct from Coordinate.
     * --------------------------
     * Usage: Move m(coordinate);
     *
     */

    Move(const Coordinate & coordinate) {
        x = coordinate.x;
        y = coordinate.y;
        playerIndex = coordinate.playerIndex;
    }

    /*
     * Method: addSign
     * Add a new sign to the index.
     * Fail: return 0: when the index is not the next index or >=3.
     * Success: return 1: write the sign and return 1.
     */

    bool addSign(const QString & newSign, int index);


    /*
     * Method: overwriteSign
     * Overwrite a signature in the specific index, where a signature
     * already exists.
     * Fail: if the signatures[index] is empty.
     *
     */

    bool overwriteSign(const QString & newSign, int index);

    int getPlayerIndex() const;


    /*
     * Method: getGrid
     * Get a size-2 QList for the x, y index.
     * --------------------------------------
     * Usage: QList grid = move.getGrid();
     */

    QList<int> getGrid() const;


    int getX() const;


    int getY() const;


    /*
     * Method: toJson
     * Return the json object of the current move, which can be easily interpretted as a string.
     * -------------------------------------------
     * Usage: QJsonObject jsonObj = move.toJson();
     */

    QJsonObject toJson();

    void setPlayerIndex(int value);

    void setX(int value);

    void setY(int value);


    /*
     * == will not compare signatures.
     */

    bool operator == (const Move & m) const;


    /*
     * fullCmp will compare signaretures.
     */

    bool fullCmp(const Move & m) const;
    QList<QString> getSignatures() const;
    void setSignatures(const QList<QString> &value);
};

void testMove();
#endif // MOVE_H
