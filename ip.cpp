#include "ip.h"

Key2 IP::getPublicKey() const
{
    return publicKey;
}

void IP::setPublicKey(const Key2 &value)
{
    publicKey = value;
}

Key2 IP::getPrivateKey() const
{
    return privateKey;
}

void IP::setPrivateKey(const Key2 &value)
{
    privateKey = value;
}

bool IP::operator==(const IP &ip) const
{
    qDebug() << "Comparing:" << address << ip.address << port << ip.port;
    return address==ip.address && port==ip.port;
}

IP &IP::operator=(const IP &ip)
{
    address = ip.address;
    port = ip.port;
    publicKey = ip.publicKey;
    privateKey = ip.privateKey;
    return *this;
}

QDebug operator<<(QDebug dbg, const IP &ip)
{
    dbg << "-----------------" << endl
       << "Address: " << ip.address << endl
       << "Port: " << ip.port << endl
       << "Full address: " << ip.getFullAddress() << endl
       << "privateKey: " << ip.privateKey << endl
       << "publicKey: " << ip.publicKey << endl;
    return dbg;
}


IP::IP(const QString &addressString, const int &p)
{
    qDebug() << "SetIP: " << addressString << p;
    setAddressFromString(addressString);
    port = p;
    qDebug() << "Set  IP:" <<  *this;
}

QList<int> IP::addressToInt() const
{
    QList<int> addressList;
    for (QString s: address.split('.'))
    {
        addressList.append(s.toInt());
    }
    return addressList;
}

QString IP::getAddress() const
{
    return address;
}

bool IP::setAddressFromString(const QString & newAddress)
{
    if (!checkAddressString(newAddress))
        return false;
    else {
        address = newAddress;
        return true;
    }
}

bool IP::setAddressFromInt(const QList<int> & newAddressInt)
{
    if (!checkAddressInt(newAddressInt))
        return false;
    else {
        address = addressIntToString(newAddressInt);
        return true;
    }

}


int IP::getPort() const
{
    return port;
}

void IP::setPort(const int & newPort)
{
    port = newPort;
}

QString IP::getFullAddress() const
{
    QString fullAddress = getAddress() + QString(':') + QString::number(port);
    return fullAddress;
}

bool IP::checkAddressInt(const QList<int> & addressInt)
{
    if (addressInt.length()!=4)
        return false;
    else {
        for (int tmp: addressInt)
        {
            if (tmp<0 || tmp>255)
                return false;
        }
    }
    return true;
}

bool IP::checkAddressString(const QString & addressString)
{
    QList<int> addressInt;
    bool valid = true;
    addressInt = addressStringToInt(addressString, valid);
    if (!valid)
        return false;
    else
        return checkAddressInt(addressInt);

}

QString IP::addressIntToString(const QList<int> & intList, bool &result)
{
    QStringList addressStringList;
    QString addressString;
    try {
        for (int i: intList)
        {
            addressStringList.append(QString::number(i));
        }
        addressString = addressStringList.join(".");
        result = true;
    } catch (...) {
        result = false;
    }
    return addressString;
}

QList<int> IP::addressStringToInt(const QString & addressString, bool& result)
{
    QList<int> addressInt;
    bool valid;
    for (QString s: addressString.split('.'))
    {
        addressInt.append(s.toInt(&valid));
        if (!valid)
        {
            result = false;
        }

    }
    return addressInt;
}

void testIP()
{
    using namespace std;
    QString testIPString;
    QString key;

    // Test initialize a IP:
    IP emptyIP, strIP(QString("123.45.67.8")), withPortIP(QString("123.45.67.8"), 1000);
    QList<int> intIP;
    intIP << 123 << 45 << 67 << 8;
    qDebug() << intIP;
    IP qListIP(intIP);
    qDebug() << "Empty IP:"<< emptyIP;
    qDebug() << "String IP:"<< strIP;
    qDebug() << "qList<int> IP:"<< qListIP;
    qDebug() << "withPortIP:"<< withPortIP;
    qDebug() << "Initialize: 1. Empty 2. String 3. qList<int> 4. withPortIP: Passed.";
    qDebug() << "setAddressFrom String, setAddressFromInt, addressIntToString: Passed.";
    qDebug() << "qDebug() << IP: Passed.";

    Q_ASSERT(strIP == qListIP);
    Q_ASSERT(!(strIP == withPortIP));
    qDebug() << "== Test Passed";
    Q_ASSERT(strIP.addressToInt() == qListIP.addressToInt());
    qDebug() << "addressToInt Test Passed.";
    IP copyIP(qListIP);
    Q_ASSERT(qListIP == copyIP);
    qDebug() << "Copy IP from an existing one: Passed.";

    qDebug() << "IP Test PASSED.";


//    int port;
//    string temp;
//    qDebug()<<"IP String: ";
//    cin >> temp;
//    testIPString = QString::fromStdString(temp);
//    IP ip;
//    if (! ip.setAddressFromString(testIPString))
//        cout<<"Error of setting address.";
//    qDebug() << ip.getAddress();


//    qDebug() <<"Port: ";
//    cin >> port;
//    ip.setPort(port);
//    qDebug() << ip.getFullAddress();


}
