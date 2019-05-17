/*
 * Class key2
 * ----------
 * This is a foundamental class for 3P4Go project.
 * It stores 2 values: a keyValue and a N, which are
 * privateKey/publicKey and N for the RSA algorithm.
 *
 * Dependency:
 * The GMP Library is required.
 *
 * Usage:
 * Key2 should be included in the IP Class.
 *
 */


#ifndef KEY2_H
#define KEY2_H

#include <QString>
#include <QStringList>
#include <gmpxx.h>
#include <QDebug>

class Key2
{

    /*
     * As RSA required, there are 2 parts of both publicKey and privateKey:
     * A specific key value and a shared N.
     * These two parts are separatedly stored.
     */

    mpz_class keyValue;

    mpz_class N;

public:
    Key2();
    Key2(mpz_class v, mpz_class n);

    /*
     * Encode a key into a string.
     * Note: toString is an alias of encode.
     */

    QString encode() const;

    QString toString() const;

    /*
     * Decode a string into a key object.
     */

    static Key2 decode(QString keyString);

    mpz_class getKeyValue() const;

    mpz_class getN() const;

    friend QDebug operator<<(QDebug dbg, const Key2 & key);
};

#endif // KEY2_H
