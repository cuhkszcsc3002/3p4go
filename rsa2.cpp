#include "rsa2.h"

RSA2::RSA2()
{

}

bool RSA2::isPrime(mpz_class x)
{
    if (x<=3)
    {
        if (x==0 || x==1) return false;
        else if (x==2 || x==3) return true;
    }

    if (x%2==0) return false;

    else {
        gmp_randclass random(gmp_randinit_default);
        random.seed(time(NULL));
        for (int i=0; i<10; i++)
        {

            mpz_class d=0;
            unsigned s = 0;

            mpz_class a = random.get_z_range(x-1);
            mpz_class x2 = x-1;
            while ((x2 & 1)==0)
            {
                s++;
                x2 = x2>>1;
            }
            d = x2;
            mpz_class mod1;
            bool resultTest2 = false;
            mod1 = powerMod(a, d, x);
            if (s==0) continue;
            else {
                    for (unsigned r=0; r<=s-1; r++) {
                        if (powerMod(a, (d*(mpz_class(1)<<r)), x) == x-1) {
                            resultTest2 = true;
                            break;
                        }
                    }
                if (mod1 != 1 && !resultTest2) return false;
                else {
                    continue;
                }
            }
        }
        return true;
    }
}

bool RSA2::isRealPrime(mpz_class x)
{
//    qDebug()<<"Checking: " << QString::fromStdString(x.get_str());
    for (mpz_class i=2; i<=sqrt(x); i++)
    {
        if (x%i==0)
            return false;
    }
    return true;
}

bool RSA2::testRandomGenerator()
{
    gmp_randclass random(gmp_randinit_default);
    random.seed(time(NULL));
    while (true)
    {
        mpz_class i = (random.get_z_bits(HALFBITS-1)<<1) + 1; // make sure odd
        while (!isPrime(i)) {
            i = (random.get_z_bits(HALFBITS-1)<<1) + 1;
        }
//        qDebug()<<"Prime:"<< QString::fromStdString(i.get_str());
    }
}

mpz_class RSA2::powerMod(mpz_class a, mpz_class b, mpz_class m)
{
    mpz_class result = 1;
    mpz_class x = a%m;
    while (b>0)
    {
        result = ((b&1)!=0) ? (result*x)%m : result;
        x = (x*x)%m;
        b >>= 1;
    }
    return result;
}

QList<Key2> RSA2::generateKey()
{
    QList<Key2> keys;
    gmp_randclass random(gmp_randinit_default);
    random.seed(time(NULL));
    mpz_class i = (random.get_z_bits(HALFBITS-1)<<1) + 1; // make sure odd
    while (!isPrime(i)) {
        i = (random.get_z_bits(HALFBITS-1)<<1) + 1;
    }
//    qDebug()<<"Generate Key:" << QString::fromStdString(i.get_str());
    mpz_class j = (random.get_z_bits(HALFBITS-1)<<1) + 1; // make sure odd
    while (!isPrime(j)) {
        j = (random.get_z_bits(HALFBITS-1)<<1) + 1;;
    }
//    qDebug()<<"Generate Key:"<< QString::fromStdString(j.get_str());

    mpz_class N = i*j;
//    qDebug()<<"N:" << QString::fromStdString(N.get_str());
    mpz_class phi = (i-1)*(j-1);
    mpz_class x=0, y=0;
    mpz_class d;
    exgcd(PUBLIC_E, phi, x, y);  // !!!!!!! ERROR, should be positive!
//    qDebug()<< "exgcd:" << PUBLIC_E << QString::fromStdString(x.get_str())
//            << QString::fromStdString(phi.get_str()) << QString::fromStdString(y.get_str());

    d = x>0?x : x + ((-x)/phi+1) * phi;

//    qDebug()<<"Public Key: "<< PUBLIC_E <<"Private Key:"<< QString::fromStdString(d.get_str());
//    keys.append(QString::number(N));
    keys.append(Key2(PUBLIC_E, N));
    keys.append(Key2(d, N));
    qDebug()<<"Key Generation Succeed.";
    return keys;
}

mpz_class RSA2::stringToInt(QString rawInfo)
{
    mpz_class info = 0;
    for (QChar c:rawInfo) {
        info <<= 8;
        info |= mpz_class(c.toLatin1());
    }
    return info;
}

mpz_class RSA2::infoToInt(QString rawInfo)
{
    rawInfo = rawInfo.mid(rawInfo.length()-ENCODELEN, ENCODELEN);
    return stringToInt(rawInfo);
}

QString RSA2::intToInfo(mpz_class data)
{
    QString result;
    mpz_class byte;
    while (data>0)
    {
        byte = data & 0xFF;
        result = char(byte.get_ui()) + result;
        data = data >> 8;
    }
    return result;
}

bool RSA2::verify(QString rawInfo, QString sign, Key2 publicKey)
{
    mpz_class sData;
    sData.set_str(sign.toStdString(), 10);
    mpz_class newData = infoToInt(rawInfo);
//    qDebug()<<"newData: "<<QString::fromStdString(newData.get_str());
    mpz_class deSign = powerMod(sData, publicKey.getKeyValue(), publicKey.getN());
    qDebug() << "deSign:" << QString::fromStdString(deSign.get_str());
    qDebug() << intToInfo(deSign);
    return deSign==newData;
}

QString RSA2::generateSign(QString rawInfo, Key2 privateKey)
{
    qDebug()<<"GenerateSign:";
    auto info = infoToInt(rawInfo);
    qDebug()<<"info:"<<QString::fromStdString(info.get_str());
    mpz_class sign = powerMod(info, privateKey.getKeyValue(), privateKey.getN());
//    qDebug()<<QString::fromStdString(info.get_str()) << ','
//           << QString::fromStdString(privateKey.keyValue.get_str()) << ','
//           << QString::fromStdString(privateKey.N.get_str())
//           << QString::fromStdString(sign.get_str());
    return QString::fromStdString(sign.get_str());
}

void RSA2::exgcd(mpz_class a, mpz_class b, mpz_class &x, mpz_class &y)
{
    mpz_class tmp;
    if (b==0 || a%b==0) {
        x = 0;
        y = 1;
        return;
    }
    exgcd(b, a%b, x, y);
//    qDebug()<<"exgcd2"<<a<<b<<x<<y;
    tmp = x;
    x = y;
    y = tmp - (a/b)*y;
//    qDebug()<<"exgcd3"<<a<<b<<x<<y;
    return;
}

void testRSA2()
{
//    Key2 key(mpz_class(100), mpz_class(300));
//    qDebug() << key.encode();
//    RSA2::testRandomGenerator();
    QList<Key2> keys = RSA2::generateKey();
    Key2 publicKey = keys.at(0);
    Key2 privateKey = keys.at(1);
    QString testString = "Hello World: C++ 123456789";
    qDebug() << "Public key: " << publicKey.encode() << "  Private key: "<< privateKey.encode();
    QString sign = RSA2::generateSign(testString, privateKey);
    qDebug() << "Sign: "<<sign;
    qDebug() << RSA2::verify(testString, sign, publicKey);

}
