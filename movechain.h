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
 *      int yourIndex = (indexOfGame + indexOfMove) % 3;
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
    QList<Move> moveList;


public:

    /*
     * Constructor
     * Initialize a moveChain object.
     * ------------------------------
     * Usage: MoveChain moveChain;
     */

    MoveChain();

    MoveChain(QString jsonString);


    /*
     * Method: nextPlayer
     * Return the playerIndex of the next player.
     * ------------------------------------------
     * Usage: int id = moveChain.nextPlayer();
     */

    int nextPlayer();


    /*
     * Method: verifyNewMove
     * Check whether the new move is validate.
     * ---------------------------------------
     * Usage: bool check = moveChain.verifyNewMove(move);
     */

    bool verifyNewMove(Move newMove);


    /*
     * Method: newMove
     * First check if it is valid. Then append it to the moveList.
     * ------------------------------------------------------------
     * Usage: bool check = moveChain.newMove();
     */

    bool newMove(Move newMove);


    /*
     * Method: checkWin
     * Check whether a specific player wins. If anyone wins, return the playerIndex.
     * If no one wins, return -1.
     * ----------------------------
     * Usage: int winner = moveChain.checkWin();
     */

    int checkWin();

    /*
     * Method: checkLastWin
     * Check whether the last move makes a player win.
     * Return true / false.
     * ----------------------------------------------
     * Usage: bool result = moveChain.checkLastWin();
     */

    bool checkLastWin(); // default testMoveChain is the moveList.
    bool checkLastWin(QList<Move>& testMoveChain);

    bool signLast(QString newSign, int index, bool forceSign=false);

    bool checkLastSign(Key2 publicKey, int index);

    /*
     * default index: the last signature.
     */

    bool checkLastSign(Key2 publicKey);



    /*
     * Method: toJson
     * Return the QJsonArray of moveChain.
     * ------------------------------------
     * Usage: QJsonArray jsonArray = moveChain.tojson();
     */

    QJsonArray toJson();

    QString toJsonString();


    /*
     * Method: abstract
     * Return an abstract of moveChain based on the x, y, playerIndex list.
     * The return length is ENCODELEN = 100 (in rsa2.h).
     * --------------------------------------------------------------------
     * Usage: QString abstract = moveChain.abstract();
     */

    QString abstract();


    bool operator<=(MoveChain& mc) const;

    int length() {return moveList.length();}


    static MoveChain jsonToMoveChain(QString jsonString);
};

void testMoveChain();

#endif // MOVECHAIN_H
