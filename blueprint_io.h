#pragma once

#include <QJsonObject>
#include <QJsonDocument>


class BluePrint_IO
{
public:
    // Can throw verror.
    static QJsonObject extract( QByteArray code );

    static QByteArray  pack( QJsonObject obj );

    static QByteArray JSonDoc( QJsonObject obj )
    {
        return QJsonDocument(obj).toJson();
    }
};
