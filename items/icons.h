#pragma once

#include <QJsonArray>
#include "item.h"
#include <map>

//=======================================================================================
class Icons
{
public:
    void load_raw( QJsonArray arr );
    void set( int idx, Item item );

    void replace_all( Item src, Item dst );

    QJsonArray build() const;

private:
    std::map<int, QJsonObject> map;
};
//=======================================================================================
