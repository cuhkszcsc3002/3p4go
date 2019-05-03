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

class Key2
{
    mpz_class keyValue;
    mpz_class N;
public:
    Key2();
    Key2(mpz_class v, mpz_class n);

    /*
     * Encode a key into a string.
     */

    QString encode();

    QString toString();

    /*
     * Decode a string into a key object.
     */

    static Key2 decode(QString keyString);
    mpz_class getKeyValue() const;
    mpz_class getN() const;
};

#endif // KEY2_H