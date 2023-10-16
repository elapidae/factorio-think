#pragma once

#include <QJsonObject>


class BluePrint_IO
{
public:
    // Can throw verror.
    static QJsonObject extract( QByteArray code );

    static QByteArray  pack( QJsonObject obj );
};
