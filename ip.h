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
#include <QtCore>
#include "key2.h"

class IP
{

    /*
     * IP.address: the IPv4 address in QString format.
     * Format: "XXX.XXX.XXX.XXX"
     * Note: The intermediate number may not be 3 digits.
     */

    QString address;


    /*
     * IP.publicKey: the public key pair of the IP.
     * For both the current player and the other players.
     */

    Key2 publicKey;


    /*
     * IP.privateKey: the private key pair of the IP.
     * For only the current player.
     */

    Key2 privateKey;

    /*
     * IP.port: the port of the player's server in int format.
     */

    int port = 0;

public:

    /*
     * Method: IP
     * The constructor of IP Class.
     * ----------------------------
     * Usage: IP ip;
     *
     */

    IP() {}

    /*
     * Method: IP(QString)
     * The constructor of IP Class by initialized with address QString.
     * -----------------------------------------------------------
     * Usage: IP ip(addressString);
     *
     */

    IP(const QString & addressString) {setAddressFromString(addressString);}

    /*
     * Method: IP(QString addressString, int port)
     * The constructor of IP Class by initialized with address QString, and its port as int.
     * -----------------------------------------------------------
     * Usage: IP ip(addressString, port);
     *
     */

    IP(const QString & addressString, const int & port) { setAddressFromString(addressString); setPort(port);}

    /*
     * Method: IP(QList<int>)
     * The constructor of IP Class by initialized with address QList<int>.
     * -----------------------------------------------------------
     * Usage: IP ip(addressInt);
     *
     */

    IP(const QList<int> & addressInt) {Q_ASSERT(setAddressFromInt(addressInt));}


    /*
     * Method: IP(ip)
     * Copy the ip to a new object.
     * ---------------------------
     * Usage: IP newIP(ip);
     *
     */

    IP(const IP & ip) {*this = ip;}


    /*
     * Method: addressToInt
     * Transfer the stored IP address string into a 4-element int vector.
     * ------------------------------------------------------------------
     * Usage: QList<int> address = ip.addressToInt();
     */

    QList<int> addressToInt() const;


    /*
     * Method: getAddress
     * Return the IP address string.
     * -----------------------------
     * Usage: QString address = ip.getAddress();
     */

    QString getAddress() const;


    /*
     * Method: setAddressFromString
     * Set the IP address string from a string. If the string is valid,
     * return true; else, return false.
     * ----------------------------------------------------------------
     * Usage: bool result = ip.setAddressFromString( QString("1.2.3.4") );
     */

    bool setAddressFromString(const QString &);


    /*
     * Method: setAddressFromInt
     * Set the IP address from a list of int. If the list of int is valid,
     * return true; else, return false.
     * -------------------------------------------------------------------
     * Usage: bool result = ip.setAddressFromInt(list);
     */

    bool setAddressFromInt(const QList<int> &);


    /*
     * Method: getPort
     * Return the port of the player.
     * ------------------------------
     * Usage: int port = ip.getPort();
     */

    int getPort() const;


    /*
     * Method: setPort
     * Set the port of the player.
     * ---------------------------
     * Usage: ip.setPort(int newPort);
     */

    void setPort(const int & newPort);


    /*
     * Method: getFullAddress
     * Get a combination of address and the port.
     * ------------------------------------------
     * Usage: QString fullAddress = ip.getFullAddress();
     */

    QString getFullAddress() const;

    /*
     * Method: checkAddressInt
     * Check if the address from an int list is valid.
     * ------------------------------------------
     * Usage: bool result = ip.checkAddressInt();
     */


    static bool checkAddressInt(const QList<int> &);

    /*
     * Method: checkAddressString
     * Check if the address from string is valid.
     * ------------------------------------------
     * Usage: bool result = ip.checkAddressString();
     */

    static bool checkAddressString(const QString &);


    /*
     * Method: addressIntToString
     * Convert an int list of address to a string format.
     * & result will be set to false if it fails.
     * --------------------------------------------------
     * Usage: QString addressString = addressintToString(QList<int>, &result);
     */

    static QString addressIntToString(const QList<int> & intList, bool &result = *(new bool));

    /*
     * Method: addressStringToInt
     * Convert a string format address to an int list format.
     * & result will be set to false if it fails.
     * --------------------------------------------------
     * Usage: QList<int> addressInt = addressStringToInt(QString, &result);
     */

    static QList<int> addressStringToInt(const QString &, bool &result = *(new bool));

    Key2 getPublicKey() const;

    void setPublicKey(const Key2 &value);

    Key2 getPrivateKey() const;

    void setPrivateKey(const Key2 &value);


    /*
     * Method: operator==
     * Compare only the address and the port. No compare with the key.
     * ---------------------------------------------------------------
     * Usage: ip1==ip2
     */

    bool operator==(const IP & ip) const;


    /*
     * Method: operator=
     * Copy the whole ip and return the result.
     * ----------------------------------------
     * Usage: IP newIP = ip;
     */

    IP & operator=(const IP& ip);

    friend QDebug operator<<(QDebug dbg, const IP & ip);

};



/*
 * Function: testIP
 * This function is used to test the IP class, but will not be used in the production.
 * -----------------------------------------------------------------------------------
 * Usage: testIP();
 */

void testIP();
#endif // IP_H
