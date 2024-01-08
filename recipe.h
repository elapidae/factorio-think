#pragma once

#include <QJsonObject>
#include "blueprint.h"

//=======================================================================================
class Recipe
{
public:
    static BluePrint make_assemble_2( QString iname, int amount );

    //  Find all assembling machines and define recipes.
    static QList<Item> extract_recipies( BluePrint bp );
    static BluePrint form_in_assembling_machine_2( Item item );

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
};
//=======================================================================================
