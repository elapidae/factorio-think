#ifndef PARSE_LUA_RECIPE_H
#define PARSE_LUA_RECIPE_H

#include <QJsonDocument>

//=======================================================================================

struct Recipe_
{
    using List = QList<Recipe_>;
    using Map  = QMap<QString,Recipe_>;

    QString name;
    int count = 0;
    int prod_time = 0;
    Map ingredients;

    QString ing_sign() const
    {
        QString res( "|" );
        for ( auto i: ingredients )
            res += i.name + "|";
        return res;
    }

    QString str() const
    {
        return QString("[%1 count:%2,\ttime:%3,\tingrs:%4]")
                .arg(name.leftJustified(35,'.'))
                .arg(count)
                .arg(prod_time)
                .arg(ingredients.size());
    }
};

//=======================================================================================

class parse_lua_recipe
{
public:
    static QJsonArray recipe();

    static Recipe_::List interpret();
};

//=======================================================================================


#endif // PARSE_LUA_RECIPE_H
