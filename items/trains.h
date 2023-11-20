#pragma once

#include "item.h"
#include "json.h"

//=======================================================================================
class Train_Stop
{
public:
    QJsonObject obj;

    void set_name( Item item, QString suffix );

    void replace( Item src, Item dst );
};
//=======================================================================================
class Schedules
{
public:
    QJsonArray arr;

    void replace( int pos, Item from, Item to );
};
//=======================================================================================
class Locomotive
{
public:
    QJsonObject obj;

    void clear_fuel();
    void coal( int count );
    void nuclear_fuel( int count );
};
