#ifndef KEY_H
#define KEY_H

#include <QtGlobal>
#include <QString>
#include <QStringList>

class Key
{


public:
    quint64 keyValue;
    quint64 N;
    Key(quint64 v, quint64 n);


    /*
     * Encode a key into a string.
     */

    QString encode();


    /*
     * Decode a string into a key object.
     */

    static Key decode(QString keyString);
};

#endif // KEY_H
