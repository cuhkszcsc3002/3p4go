#ifndef NEWMOVE_H
#define NEWMOVE_H

#include <QString>
#include <string>



class Newmove
{
public:

    /*
     * method: constructor
     * The constructor of the Newmove object.
     * -------------------------------------
     * Usage: Newmove newmove;
     * This method checks every new move.
     */

    Newmove();


    /*
     * Method: newclick
     * Usage:
     * ---------------------------------------
     * This method is called by GUI.newclick(),
     * and used to call client.sendForSig().
     */

    void newclick();

    /*
     * Method: validateForSig
     * Usage:
     * ---------------------------------------
     * This method is called by Server.receiveSigReq(),
     * and used to prevent cheating. It will check whether
     * there are differences on the signatures and coordinaries.
     * Game.acceptForSig() will be called if this
     * method returns 1, otherwise, Game.rejectForSig()
     * will be called.
     */

    bool validateForSig();

    /*
     * Method: acceptForSig
     * Usage:
     * ---------------------------------------
     * This method is called if Newmove.validateForSig()
     * returns 1, and it will call Server.acceptSig().
     */

    void acceptForSig();

    /*
     * Method: rejectForSig
     * Usage:
     * ---------------------------------------
     * This method is called if Newmove.validateForSig()
     * returns 0, and it will call Server.rejectSig().
     */

    void rejectForSig();

    /*
     * Method:
     * Usage:
     * ---------------------------------------
     * This method is called by , and used to call
     */

    QString sigAccepted();

    /*
     * Method:
     * Usage:
     * ---------------------------------------
     * This method is called by , and used to call
     */

    QString sigRejected();

    /*
     * Method:
     * Usage:
     * ---------------------------------------
     * This method is called by , and used to call
     */

    bool collectAllSig();

   /* For the one who own the newmove*/

    /*
     * Method:
     * Usage:
     * ---------------------------------------
     * This method is called by , and used to call
     */


    void broadcastNewmove();

  /* For the others */

    /*
     * Method:
     * Usage:
     * ---------------------------------------
     * This method is called by , and used to call
     */


    bool checkNewmove();

    /*
     * Method:
     * Usage:
     * ---------------------------------------
     * This method is called by , and used to call
     */

    void acceptNewmove();

    /*
     * Method:
     * Usage:
     * ---------------------------------------
     * This method is called by , and used to call
     */

    void rejectNewmove();

    /*
     * Method:
     * Usage:
     * ---------------------------------------
     * This method is called by , and used to call
     */

    QString updateNewmove();

    void finish();

    int history();

    void exit();

};
#endif // NEWMOVE_H
