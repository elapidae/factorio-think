#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>

#include "vlog.h"

class BluePrint
{
public:
    //  Здесь будем извлевать из кода синенького структуру.
    static QJsonObject extract(QByteArray code);

    static QByteArray  pack(QJsonObject obj);

    static QJsonObject correct_landfill(QJsonObject src);

    static QJsonObject correct_blueprint_landfill(QJsonObject src);
};
