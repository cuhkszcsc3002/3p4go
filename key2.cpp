#include "key2.h"

mpz_class Key2::getKeyValue() const
{
    return keyValue;
}

mpz_class Key2::getN() const
{
    return N;
}

Key2 Key2::operator=(const Key2 & newKey)
{
    keyValue = newKey.keyValue;
    N = newKey.N;
    return *this;
}

QDebug operator<<(QDebug dbg, const Key2 &key)
{
    dbg << "---------------------\n"
        << "Key value: " << QString::fromStdString(key.keyValue.get_str()) << endl
        << "Key N: " << QString::fromStdString(key.N.get_str()) << endl;
    return dbg;

}

Key2::Key2()
{
    keyValue = 0;
    N = 0;
}

Key2::Key2(mpz_class v, mpz_class n)
{
    keyValue = v;
    N = n;
}

QString Key2::encode() const
{
    QString encodeString = QString::fromStdString(keyValue.get_str() + "&" + N.get_str());
    return encodeString;
}

QString Key2::toString() const
{
    return encode();
}

Key2 Key2::decode(QString keyString)
{
    auto ql = keyString.split("&");
    mpz_class keyValue;
    keyValue.set_str(ql[0].toStdString(), 10);
    mpz_class N;
    N.set_str(ql[1].toStdString(), 10);
    Key2 newKey(keyValue, N);
    return newKey;
}
