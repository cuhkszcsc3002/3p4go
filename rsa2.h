/*
 * This is the RSA implementation using GMP lib.
 * An efficient RSA algorithm library depending on GMP Library.
 *
 * -----------------------------------------------------------
 *
 * Requirements:
 * 1. GMP installed
 * 2. key2.h and key2.h
 *
 * ---------------------
 *
 * Common Usage:
 *
 * 1. Generate Keys:
 * QList<Key2> keys = RSA::generateKey();
 * Key2 publicKey = keys.at(0);
 * Key2 privateKey = keys.at(1);
 *
 * 2. Sign a QString:
 * QString sign = RSA2::generateSign(string, privateKey);
 *
 * Note: For non-QString object, one more step transferring
 * to QString is required.
 *
 *
 * 3. Verify a Sign:
 * RSA2::verify(originString, signString, publicKey);
 * Returns true / false.
 *
 * ---------------------------------------------------------
 *
 * Implementations Notes:
 * 1. The prime detection is based on Miller-Rabin Test,
 * with 10-time random check. The probability of mistake
 * is theroetically 4^(-10).
 * 2. To ensure the effeciency, bit operations are widely used
 * in the implementation.
 * 3. powerMod is a dedicate function which calculates a^b mod m.
 * It is been optimized using bit operations to reduce the
 * computational complexity.
 * 4. BITS = 1024 and HALFBITS = 512 are two constants for the
 * length of keys. It may be changed to a greater number.
 *
 */

#ifndef RSA2_H
#define RSA2_H

#include <QList>
#include <QString>
#include <QtDebug>
#include <iostream>
#include <gmpxx.h>
#include "key2.h"

#define ENCODELEN 100
#define PUBLIC_E 65537
#define BITS 1024
#define HALFBITS 512

class RSA2
{

public:
    RSA2();

    /*
     * Method: isPrime
     * Used to test an unsigned int is a prime using Miller-Rabin Test.
     * ----------------------------------------------------------------
     * Usage: bool result = isPrime(x);
     */

    static bool isPrime(mpz_class x);

    /*
     * Method: isRealPrime
     * A method to check whether a "prime" having passed Miller-Rabin Test is a real prime.
     * ------------------------------------------------------------------------------------
     * Usage: bool result = isRealPrime(x);
     */

    static bool isRealPrime(mpz_class x);

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

    static mpz_class powerMod(mpz_class a, mpz_class b, mpz_class m);


    /*
     * Method: generateKey
     * Used to generate 1 public key and 1 private key. Public Key in index 0; Private Key in index 1.
     * -----------------------------------------------------------------------------------------------
     * Usage: QList<QString> keys = generateKey();
     * QString publicKey = keys[0];
     * QString privateKey = keys[1];
     */

    static QList<Key2> generateKey();


    /* Method: stringToInt
     * Transfer a string(no more than 8 chars) to an quint64 int.
     * ----------------------------------------------------------
     * Usage: quint64 result = stringToInt(rawString);
     */

    static mpz_class stringToInt(QString rawInfo);


    /*
     * Method: infoToInt
     * Transfer a string to an quint64 int by extracting the last 8 chars and using their ascii codes.
     * -----------------------------------------------------------------------------------------------
     * Usage: quint64 info = infoToInt(infoString);
     */

    static mpz_class infoToInt(QString rawInfo);

    static QString intToInfo(mpz_class data);

    /*
     * Method: verify
     * Used to verify whether a signature is valid.
     * ----------------------------------------------
     * Usage: bool result = verify(raw, sign, publicKey);
     */

    static bool verify(QString rawInfo, QString sign, Key2 publicKey);


    /*
     * Method: generateSign
     * Used to sign a message with a private key.
     * -----------------------------------------
     * Usage: QString sign = generateSign(raw, privateKey);
     */

    static QString generateSign(QString rawInfo, Key2 privateKey);

    static void exgcd(mpz_class a, mpz_class b, mpz_class &x, mpz_class &y);
};

void testRSA2();

#endif // RSA2_H
