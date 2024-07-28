#pragma once

#include <QJsonObject>
#include <QJsonArray>
#include "item.h"
#include "recipe.h"
#include "vlog.h"

//=======================================================================================
class Constant_Combinator
{
public:
    static constexpr auto name = "constant-combinator";
    static auto get() { return Item::get("constant-combinator"); }



    QJsonObject obj;

    void clear_behavior();

    // index from 1!
    void set_behavior( int index, Item item, int count );

    Item get_item( int index );

    //  NB! Maybe bad idea!
    // - set all values to zero;
    // - move to the beginning;
    // - remove direction;
    void normalize_as_info();

    void remove_direction();
    void replace_all( Item src, Item dst );
    void save_recipe( Recipe recipe );
    bool contains( Item item ) const;

//private:
    QJsonArray filters() const;
    void filters( QJsonArray );
};
//=======================================================================================
class Constant_CombinatorRef
{
public:
    Constant_CombinatorRef( QJsonValueRef ref );

    static Constant_CombinatorRef find( QList<QJsonValueRef> where, Item what );

    void clear_behavior();
    void replace_all( Item src, Item dst );
    void save_recipe( Recipe recipe );
    bool contains( Item item ) const;
    void set_behavior( int index, Item item, int count );

private:
    QJsonValueRef ref;
};
//=======================================================================================
