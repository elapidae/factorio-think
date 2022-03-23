#ifndef BLUEPRINT_H
#define BLUEPRINT_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>


class BluePrint
{
public:
    //  Здесь будем извлевать из кода синенького структуру.
    static QJsonObject extract(QByteArray code);
    static QByteArray  pack(QJsonObject obj);

    static QJsonObject correct_landfill(QJsonObject src);
};

#endif // BLUEPRINT_H
