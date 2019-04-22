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
     * Method: sigAccepted
     * Usage: 
     * ---------------------------------------
     * This method is called if Client.sendForSig() returns 1.
     * It will save signatures and inform the one who send the
     * sig_string of that he has accepted the history chain and
     * signatures.
     */

    QString sigAccepted();

    /*
     * Method: sigRejected
     * Usage:
     * ---------------------------------------
     * This method is called if Client.sendForSig() returns 0.
     * It will ask the one who send the sig_string to send a
     * new history chain in correct vector format and signature.
     */

    QString sigRejected(std::string ones_IP);
    
    
   /* For the one who own the newmove*/
    
    /*
     * Method: collectAllSig
     * Usage:
     * ----------------------------------------------------
     * This method is called after Newmove.validateForSig(),
     * and used to check whether they have collected all
     * signatures.
     */

    bool collectAllSig();
 //
    /*
     * Method: broadcastNewmove
     * Usage: 
     * -------------------------------------------
     * This method is called by , and used to call
     */

    void broadcastNewmove();

  /* For the others */

    /*
     * Method: checkNewmove
     * Usage: 
     * ---------------------------------------
     * This method is called by Server.receiveNewmove(),
     * and used to call Newmove.acceptNewmove() or
     * Newmove.rejectNewmove(). If the newmove is valid
     * (it returns 1), Newmove.acceptNewmove() is called;
     * otherwise, Newmove.rejectNewmove() is called.
     */

    bool checkNewmove();

    /*
     * Method: acceptNewmove
     * Usage:
     * ---------------------------------------
     * This method is called when Newmove.checkNewmove()
     * returns 1, and used to call Server.acceptNewmove().
     */

    void acceptNewmove();

    /*
     * Method: rejectNewmove
     * Usage:
     * ---------------------------------------
     * This method is called when Newmove.checkNewmove()
     * returns 0, and used to call Server.rejectNewmove().
     */

    void rejectNewmove();

    /*
     * Method: updateNewmove
     * Usage:
     * ---------------------------------------
     * This method is called by Newmove.broadcastNewmove(),
     * and used to call GUI.updateNewmove().
     */

    QString updateNewmove();


};
#endif // NEWMOVE_H
