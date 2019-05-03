#include "key2.h"

mpz_class Key2::getKeyValue() const
{
    return keyValue;
}

mpz_class Key2::getN() const
{
    return N;
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

QString Key2::encode()
{
    QString encodeString = QString::fromStdString(keyValue.get_str() + "&" + N.get_str());
    return encodeString;
}

QString Key2::toString()
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
