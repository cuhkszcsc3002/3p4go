#include "rsa.h"

RSA::RSA()
{

}

bool RSA::isPrime(quint64 x)
{
    if (x<=3)
    {
        switch (x)
        {
        case 0:
        case 1: return false;
        case 2:
        case 3: return true;
        default: return false;
        }
    }
    if (!(x&1)) return false;

    else {

        quint64 s=0, d=0;
        quint32 range1 = (x-1)>>32;
        quint32 range2 = (((x-1)<<32)>>32);
        quint32 rand1 = QRandomGenerator::global()->bounded(range1),
                rand2 = (range1>0)? quint32(QRandomGenerator::global()->generate()) : QRandomGenerator::global()->bounded(range2);
        quint64 a = (quint64(rand1)<<32) + rand2;
        quint64 x2 = x-1;
        while (!(x2 & 1))
        {
            s++;
            x2 = x2>>1;
        }
        d = x2;
        quint64 mod1;
        bool resultTest2 = false;
        mod1 = powerMod(a, d, x);
        if (s==0) return isRealPrime(x);
        else {
                for (quint64 r=0; r<=s-1; r++) {
                    if (powerMod(a, (d*(1<<r)), x) == x-1) {
                        resultTest2 = true;
                        break;
                    }
                }

            if (mod1 != 1 && !resultTest2) return false;
            else {
                return isRealPrime(x);
            }
        }

    }
}

bool RSA::isRealPrime(quint64 x)
{
//    return true;
    qDebug()<<"Checking: " << x;
    for (quint64 i=2; i<=sqrt(x); i++)
    {
        if (x%i==0)
            return false;
    }
    return true;
}

bool RSA::testRandomGenerator()
{
    while (true)
    {
        quint64 i =(((quint64(1)<<28) + QRandomGenerator::global()->bounded(quint32(1)<<27))<<1) + 1; // make sure odd
//        qDebug()<< i << bin<<i;

        while (!isPrime(i)) {
            i =(((quint64(1)<<28) + QRandomGenerator::global()->bounded(quint32(1)<<27))<<1) + 1;
//            qDebug()<< i << bin<<i;

        }
        qDebug()<<"Prime:"<< i << bin<<i;
    }
}



/*
 * Method: powerMod
 * This will return (a^b) mod m.
 * It is an extremely fast algorithm, which requires only 4*log(B)
 * (B is the number of bits of b) operations.
 * And most operations are bit operations which perform very fast.
 */

quint64 RSA::powerMod(quint64 a, quint64 b, quint64 m)
{
    quint64 result = 1;
    quint64 x = a;
    while (b)
    {
        result = (b&1)?(result*x)%m:result;
        x = (x*x)%m;
        b >>= 1;
    }
    return result;
}

QList<Key> RSA::generateKey()
{
    QList<Key> keys;
    quint64 i =(((quint64(1)<<29) + QRandomGenerator::global()->bounded(quint32(1)<<28))<<1) + 1; // make sure odd
    while (!isPrime(i)) {
        i =(((quint64(1)<<29) + QRandomGenerator::global()->bounded(quint32(1)<<28))<<1) + 1;
//        qDebug()<<i;

    }
    qDebug()<<"Generate Key:" << i;
//    keys.append(QString::number(i));
    quint64 j =(((quint64(1)<<29) + QRandomGenerator::global()->bounded(quint32(1)<<28))<<1) + 1; // make sure odd
    while (!isPrime(j)) {
        j =(((quint64(1)<<29) + QRandomGenerator::global()->bounded(quint32(1)<<28))<<1) + 1;
//        qDebug()<<j;

    }
    qDebug()<<"Generate Key:"<<j;

    quint64 N = i*j;
    qDebug()<<"N:" << N;
    quint64 phi = (i-1)*(j-1);
    quint64 x=0, y=0, d;
    exgcd(phi, PUBLIC_E, x, y);
    d = x>0?x:y;

    qDebug()<<"Public Key: "<<PUBLIC_E<<"Private Key:"<<d;
//    keys.append(QString::number(N));
    keys.append(Key(PUBLIC_E, N));
    keys.append(Key(d, N));
    qDebug()<<"return keys";
    return keys;
}

quint64 RSA::stringToInt(QString rawInfo)
{
    quint64 info = 0;
    for (QChar c:rawInfo) {
        info <<= 8;
        info |= quint64(c.toLatin1());
    }
    return info;
}

quint64 RSA::infoToInt(QString rawInfo)
{
    rawInfo = rawInfo.mid(rawInfo.length()-8, 8);
    return stringToInt(rawInfo);
}

bool RSA::validate(QString rawInfo, QString sign, Key publicKey)
{
        quint64 sData = sign.toULongLong();
        quint64 newData = infoToInt(rawInfo);
        qDebug()<<"newData: "<<newData << "sign:" << sData << sign;
        quint64 deSign = powerMod(sData, publicKey.keyValue, publicKey.N);
        qDebug() << "deSign:" << deSign;
        //    quint64 newData = powerMod(sign, priKey, )
}



QString RSA::generateSign(QString rawInfo, Key privateKey)
{
    qDebug()<<"GenerateSign:";
    auto info = infoToInt(rawInfo);
    qDebug()<<"info:"<<info;
    quint64 sign = powerMod(info, privateKey.keyValue, privateKey.N);
    return QString::number(sign);
}

quint64 RSA::exgcd(quint64 a, quint64 b, quint64 &x, quint64 &y)
{
    if (b>a) return exgcd(b, a, x, y);
    if (b==0) {
        x = 1;
        y = 0;
        return a;
    }
    quint64 r = exgcd(b, a%b, x, y);
    quint64 t = x;
    x = y;
    y = t - (a/b) * y;
    return r;
}

void testRSA()
{
    QList<Key> keys = RSA::generateKey();
    Key publicKey = keys.at(0);
    Key privateKey = keys.at(1);
    qDebug() << "Public key: " << publicKey.encode() << "  Private key: "<< privateKey.encode();
    QString sign = RSA::generateSign("hello world", privateKey);
    qDebug() << "Sign: "<<sign;
    RSA::validate("hello world", sign, publicKey);
}
