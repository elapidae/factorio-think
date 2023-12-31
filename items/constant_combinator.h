#pragma once

#include <QJsonObject>
#include <QJsonArray>
#include "item.h"
#include "recipe.h"

//=======================================================================================
class Constant_Combinator
{
public:
    static constexpr auto json_name = "constant-combinator";

    QJsonObject obj;

    void clear_behavior();

    // index from 1!
    void set_behavior( int index, Item item, int count );

    //  NB! Maybe vad idea!
    // - set all values to zero;
    // - move to the beginning;
    // - remove direction;
    void normalize_as_info();

    void replace_all( Item src, Item dst );

    void save_recipe( Recipe recipe );

private:
    QJsonArray filters() const;
    void filters( QJsonArray );
};
//=======================================================================================
class Constant_Combinator2
{
public:
    Constant_Combinator2( QJsonValueRef ref ) : ref( ref ) {}

    void replace( Item src, Item dst )
    {
        Constant_Combinator cc{ ref.toObject() };
        cc.replace_all( src, dst );
        ref = cc.obj;
    }
private:
    QJsonValueRef ref;
};
//=======================================================================================
