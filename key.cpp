#include "key.h"

Key::Key()
{
    keyValue = 0;
    N = 0;
}

Key::Key(quint64 v, quint64 n)
{
    keyValue = v;
    N = n;
}

QString Key::encode()
{
    QString encodeString = QString::number(keyValue) + "&" + QString::number(N);
    return encodeString;
}

QString Key::toString()
{
    return encode();
}

Key Key::decode(QString keyString)
{
    auto ql = keyString.split("&");
    quint64 keyValue = ql[0].toULongLong();
    quint64 N = ql[1].toULongLong();
    Key newKey(keyValue, N);
    return newKey;
}
