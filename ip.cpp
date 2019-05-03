#include "ip.h"

IP::IP()
{
    address = QString();
    key = Key();
}


QList<int> IP::adressToInt()
{
    QList<int> addressList;
    for (QString s: address.split('.'))
    {
        addressList.append(s.toInt());
    }
    return addressList;
}

QString IP::getAddress()
{
    return address;
}

bool IP::setAddressFromString(QString newAddress)
{
    if (!checkAddressString(newAddress))
        return false;
    else {
        address = newAddress;
        return true;
    }
}

bool IP::setAddressFromInt(QList<int> newAddressInt)
{
    if (!checkAddressInt(newAddressInt))
        return false;
    else {
        address = addressIntToString(newAddressInt);
        return true;
    }

}

void IP::setKey(Key2 newKey)
{
    key2 = newKey;
}

Key2 IP::getKey()
{
    return key;
}

int IP::getPort()
{
    return port;
}

void IP::setPort(int newPort)
{
    port = newPort;
}

QString IP::getFullAddress()
{
    QString fullAddress = getAddress() + QString(':') + QString::number(port);
    return fullAddress;
}

bool IP::checkAddressInt(QList<int> addressInt)
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

bool IP::checkAddressString(QString addressString)
{
    QList<int> addressInt;
    bool valid = true;
    addressInt = addressStringToInt(addressString, valid);
    if (!valid)
        return false;
    else
        return checkAddressInt(addressInt);

}

QString IP::addressIntToString(QList<int> intList, bool &result)
{
    QStringList addressStringList;
    QString addressString;
    try {
        for (int i: intList)
        {
            addressStringList.append(QString(i));
        }
        addressString = addressStringList.join(".");
        result = true;
    } catch (...) {
        result = false;
    }

    return addressString;
}

QList<int> IP::addressStringToInt(QString addressString, bool& result)
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
    int port;
    string temp;
    qDebug()<<"IP String: ";
    cin >> temp;
    testIPString = QString::fromStdString(temp);
    IP ip;
    if (! ip.setAddressFromString(testIPString))
        cout<<"Error of setting address.";
    qDebug() << ip.getAddress();


    qDebug() <<"Port: ";
    cin >> port;
    ip.setPort(port);
    qDebug() << ip.getFullAddress();


}
