/*
 * This file is for prototype of the class IP.
 * IP consists of the IP address information and the public key of the corresponding IP.
 */

#ifndef IP_H
#define IP_H

#include <QString>
#include <QList>
#include <iostream>
#include <string>
#include <QDebug>
#include "key.h"

class IP
{
    /*
     * IP.address stores the IPv4 address.
     * Format: "XXX.XXX.XXX.XXX"
     * Note: The intermediate number may not be 3 digits.
     */

    QString address;


    /*
     * IP.key stores the public key of the current player.
     * Format: 1024-length string(length may vary).
     */

    QString key;


    /*
     * IP.port stores the port of the player's server.
     * It is stored as an int.
     */

    int port;

public:

    /*
     * Method: IP
     * The constructor of IP Class.
     * ----------------------------
     * Usage: IP ip;
     *
     */

    IP();


    /*
     * Method: addressToInt
     * Transfer the stored IP address string into a 4-element int vector.
     * ------------------------------------------------------------------
     * Usage: QList<int> address = ip.addressToInt();
     */

    QList<int> adressToInt();


    /*
     * Method: getAddress
     * Return the IP address string.
     * -----------------------------
     * Usage: QString address = ip.getAddress();
     */

    QString getAddress();


    /*
     * Method: setAddressFromString
     * Set the IP address string from a string. If the string is valid,
     * return true; else, return false.
     * ----------------------------------------------------------------
     * Usage: bool result = ip.setAddressFromString( QString("1.2.3.4") );
     */

    bool setAddressFromString(QString);


    /*
     * Method: setAddressFromInt
     * Set the IP address from a list of int. If the list of int is valid,
     * return true; else, return false.
     * -------------------------------------------------------------------
     * Usage: bool result = ip.setAddressFromInt(list);
     */

    bool setAddressFromInt(QList<int>);


    /*
     * Method: setKey
     * Set the key of the corresponding IP.
     * ------------------------------------
     * Usage: ip.setKey( QString("key") );
     */

    void setKey(QString);


    /*
     * Method: getKey
     * Get the key of the corresponding IP.
     * ------------------------------------
     * Usage: QString key = ip.getkey();
     */

    QString getKey();


    /*
     * Method: getPort
     * Return the port of the player.
     * ------------------------------
     * Usage: int port = ip.getPort();
     */

    int getPort();


    /*
     * Method: setPort
     * Set the port of the player.
     * ---------------------------
     * Usage: ip.setPort(int newPort);
     */

    void setPort(int newPort);


    /*
     * Method: getFullAddress
     * Get a combination of address and the port.
     * ------------------------------------------
     * Usage: QString fullAddress = ip.getFullAddress();
     */

    QString getFullAddress();

    /*
     * Method: checkAddressInt
     * Check if the address from an int list is valid.
     * ------------------------------------------
     * Usage: bool result = ip.checkAddressInt();
     */


    static bool checkAddressInt(QList<int>);

    /*
     * Method: checkAddressString
     * Check if the address from string is valid.
     * ------------------------------------------
     * Usage: bool result = ip.checkAddressString();
     */

    static bool checkAddressString(QString);


    /*
     * Method: addressIntToString
     * Convert an int list of address to a string format.
     * & result will be set to false if it fails.
     * --------------------------------------------------
     * Usage: QString addressString = addressintToString(QList<int>, &result);
     */

    static QString addressIntToString(QList<int>, bool &result = *(new bool));

    /*
     * Method: addressStringToInt
     * Convert a string format address to an int list format.
     * & result will be set to false if it fails.
     * --------------------------------------------------
     * Usage: QList<int> addressInt = addressStringToInt(QString, &result);
     */

    static QList<int> addressStringToInt(QString, bool &result = *(new bool));

};


/*
 * Function: testIP
 * This function is used to test the IP class, but will not be used in the production.
 * -----------------------------------------------------------------------------------
 * Usage: testIP();
 */

void testIP();
#endif // IP_H
