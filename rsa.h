/*
 * Class RSA
 * RSA is a widely-used encryption algorithm. All codes in this RSA
 * class is written by us. Only the algorithm is by reference.
 */

#ifndef RSA_H
#define RSA_H

#include <QList>
#include <QString>
#include <QRandomGenerator>
#include <QtDebug>
#include <iostream>
#include "key.h"

#define ENCODELEN 8
#define PUBLIC_E 65537

class RSA
{

public:
    RSA();

    /*
     * Method: isPrime
     * Used to test an unsigned int is a prime using Miller-Rabin Test.
     * ----------------------------------------------------------------
     * Usage: bool result = isPrime(x);
     */

    static bool isPrime(quint64 x);

    /*
     * Method: isRealPrime
     * A method to check whether a "prime" having passed Miller-Rabin Test is a real prime.
     * ------------------------------------------------------------------------------------
     * Usage: bool result = isRealPrime(x);
     */

    static bool isRealPrime(quint64 x);

    /*
     * Method: generateKey
     * Used to generate a pair of public key (position 0) and private key (position 1).
     * --------------------------------------------------------------------------------
     * Usage: QList<QString> newKey = generateKey();
     */

    static bool testRandomGenerator();

    /*
     * Method: powerMod
     * Return a^b mod m
     * ----------------
     * Usage: quint64 result = powerMod(a, b, m);
     */

    static quint64 powerMod(quint64 a, quint64 b, quint64 m);


    /*
     * Method: generateKey
     * Used to generate 1 public key and 1 private key. Public Key in index 0; Private Key in index 1.
     * -----------------------------------------------------------------------------------------------
     * Usage: QList<QString> keys = generateKey();
     * QString publicKey = keys[0];
     * QString privateKey = keys[1];
     */

    static QList<Key> generateKey();


    /* Method: stringToInt
     * Transfer a string(no more than 8 chars) to an quint64 int.
     * ----------------------------------------------------------
     * Usage: quint64 result = stringToInt(rawString);
     */

    static quint64 stringToInt(QString rawInfo);


    /*
     * Method: infoToInt
     * Transfer a string to an quint64 int by extracting the last 8 chars and using their ascii codes.
     * -----------------------------------------------------------------------------------------------
     * Usage: quint64 info = infoToInt(infoString);
     */

    static quint64 infoToInt(QString rawInfo);

    /*
     * Method: validate
     * Used to validate whether a signature is valid.
     * ----------------------------------------------
     * Usage: bool result = validate(raw, sign, publicKey);
     */

    static bool validate(QString rawInfo, QString sign, Key publicKey);


    /*
     * Method: generateSign
     * Used to sign a message with a private key.
     * -----------------------------------------
     * Usage: QString sign = generateSign(raw, privateKey);
     */

    static QString generateSign(QString rawInfo, Key privateKey);

    static quint64 exgcd(quint64 a, quint64 b, quint64 &x, quint64 &y);
};

void testRSA();

#endif // RSA_H
