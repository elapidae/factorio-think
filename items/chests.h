#pragma once

#include <QJsonObject>
#include "qdeb.h"
#include "item.h"

//=======================================================================================
class Chests
{
public:
    // Wooden
    static Item wooden_chest()
    { return Item::get("wooden-chest"); }

    //  Steel
    static Item steel_chest()
    { return Item::get("steel-chest"); }

    // Yellow
    static Item chest_storage()
    { return Item::get("logistic-chest-storage"); }

    // Red
    static Item chest_passive_provider()
    { return Item::get("logistic-chest-passive-provider"); }

    // Magenta
    static Item chest_active_provider()
    { return Item::get("logistic-chest-active-provider"); }

    // Green
    static Item chest_buffer()
    { return Item::get("logistic-chest-buffer"); }

    // Blue
    static Item chest_requester()
    { return Item::get("logistic-chest-requester"); }

    class Storage;
    class Requester;
};
//=======================================================================================
class Chests::Storage
{
public:
    QJsonValueRef ref;

    void filter( Item item );
};
//=======================================================================================
class Chests::Requester
{
public:
    QJsonValueRef ref;

    void request( int pos, Item it, int count )
    {
        (void)pos; (void)count; (void)it;
        qdeb << ref;
    }
};
//=======================================================================================
