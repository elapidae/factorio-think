#pragma once

#include <QJsonObject>
#include "blueprint.h"

//=======================================================================================
class Recipe
{
public:
    static BluePrint make_assemble_2( QString iname, int amount );

    struct Ingredient
    {
        QString name;
        int amount;
        using List = QList<Ingredient>;
    };

    static QStringList keys();
    static Recipe get( QString name );

    QString name;
    Ingredient::List ingredients;
    int amount;

private:
    static QJsonObject bp_gen0();
};
//=======================================================================================
