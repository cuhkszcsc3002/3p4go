#include "key.h"

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

Key Key::decode(QString keyString)
{
    auto ql = keyString.split("&");
    quint64 keyValue = ql[0].toULongLong();
    quint64 N = ql[1].toLongLong();
    Key newKey(keyValue, N);
    return newKey;
}
