/*
 * Class: MoveChain
 * MoveChain stores and maintains a list of moves.
 *
 * -----------------------------------------------
 *
 * Sample Usage:
 * 1. Create an empty MoveChain.
 * MoveChain mc;
 *
 * 2. Transferring a moveChain json string to a MoveChain object.
 * MoveChain mc(jsonString);
 *
 * 3. Verify if a new move is suitable.
 * bool check = mc.verifyNewMove(newMove);
 *
 * 4. Add a signature to the last move.
 * 4.1 Get an abstract of the moveChain:
 *      QString absStr = mc.abstract();
 * 4.2 Sign the abstract with the key:
 *      QString newSign = RSA2::generateSign(absStr, privateKey);
 * 4.3 Add the sign to mc:
 *  4.3.1) If you are the host of move:
 *      mc.signLast(newSign, 0);
 *  4.3.2) If you are the guest of move:
 *      int (my objective Index) = (3 + myIndex - playerIndex) % 3;
 *      mc.signLast(newSign, yourIndex);
 *
 * 5. Generate a json string, which can be sent out.
 * QString jsonString = mc.toJsonString();
 *
 * Note: this string can be used to construct the same MoveChain
 * object again by simply:
 * MoveChain mc(jsonString); or
 * MoveChain mc = jsonToMoveChain(jsonString);
 *
 * 6. Compare two moveChain with <= , which ignores the last object
 * of both moveChain, and checks the proceding ones if they are the
 * same.
 * This is useful when you receive a new moveChain from others.
 *
 * mc1 <= mc2.
 *
 * 7. Check the signature of the last move:
 * bool check = mc.checkLastSign(publicKey, index); // index is 0, 1, 2, the signature's index.
 * or bool check = mc.checkLastSign(publicKey); // index is default to be the last signature.
 *
 */

#ifndef MOVECHAIN_H
#define MOVECHAIN_H

#include <QList>
#include <QJsonArray>
#include <QJsonDocument>
#include "move.h"
#include <iostream>
#include "rsa2.h"

class Game;

class MoveChain
{

public:
    QList<Move> moveList;


    /*
     * Constructor
     * Initialize a moveChain object.
     * ------------------------------
     * Usage: MoveChain moveChain;
     */

    MoveChain();

    MoveChain(const QString & jsonString);


    /*
     * Method: nextPlayer
     * Return the playerIndex of the next player.
     * ------------------------------------------
     * Usage: int id = moveChain.nextPlayer();
     */

    int nextPlayer() const;


    /*
     * Method: verifyNewMove
     * Check whether the new move is validate.
     * ---------------------------------------
     * Usage: bool check = moveChain.verifyNewMove(move);
     */

    bool verifyNewMove(const Move & newMove) const;


    /*
     * Method: newMove
     * First check if it is valid. Then append it to the moveList.
     * ------------------------------------------------------------
     * Usage: bool check = moveChain.newMove();
     */

    bool newMove(const Move & newMove);


    /*
     * Method: checkWin
     * Check whether a specific player wins. If anyone wins, return the playerIndex.
     * If no one wins, return -1.
     * ----------------------------
     * Usage: int winner = moveChain.checkWin();
     */

    int checkWin() const;

    /*
     * Method: checkLastWin
     * Check whether the last move makes a player win.
     * Return true / false.
     * ----------------------------------------------
     * Usage: bool result = moveChain.checkLastWin();
     */

    bool checkLastWin() const; // default testMoveChain is the moveList.
    bool checkLastWin(const QList<Move>& testMoveChain) const;

    bool signLast(QString newSign);
    bool signLast(QString newSign, int index);

    bool checkLastSign(const Key2 & publicKey, int index) const;

    /*
     * default index: the last signature.
     */

    bool checkLastSign(const Key2 & publicKey) const;



    /*
     * Method: toJson
     * Return the QJsonArray of moveChain.
     * ------------------------------------
     * Usage: QJsonArray jsonArray = moveChain.tojson();
     */

    QJsonArray toJson() const;

    QString toJsonString() const;


    /*
     * Method: abstract
     * Return an abstract of moveChain based on the x, y, playerIndex list.
     * The return length is ENCODELEN = 100 (in rsa2.h).
     * --------------------------------------------------------------------
     * Usage: QString abstract = moveChain.abstract();
     */

    QString abstract() const;


    bool operator<=(const MoveChain & mc) const;

    int length() const {return moveList.length();}


    static MoveChain jsonToMoveChain(const QString & jsonString);
};

void testMoveChain();

#endif // MOVECHAIN_H
