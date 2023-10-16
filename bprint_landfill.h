#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>

#include "vlog.h"

class BPrint_Landfill
{
public:
    // Works with object "blueprint"
    static QJsonObject correct_landfill( QJsonObject src );

    // Extract 'blueprint' field from src, then do 'correct_landfill()', then put
    // result to new object with key 'blueprint'
    static QJsonObject correct_blueprint_landfill( QJsonObject src );
};
