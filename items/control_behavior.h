#pragma once

#include "item.h"

#include "vlog.h"
#include "qdeb.h"

//=======================================================================================
class Circuit_Condition
{
public:
    QJsonValueRef ref;

    int constant() const;
    void constant( int val );
};
//=======================================================================================
class Filters
{
public:
    QJsonValueRef ref;

};
//=======================================================================================
class Control_Behavior
{
public:
    QJsonValueRef ref;

    Filters filters();
    void filters (Filters f);

    void circuit_condition_constant( int val );
};
//=======================================================================================
