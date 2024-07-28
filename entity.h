#pragma once

#include "json.h"

//=======================================================================================
class Entity
{
public:
    Entity( QJsonValueRef ref );

    void shift( int x, int y );

    QJsonValueRef ref;
};
//=======================================================================================
