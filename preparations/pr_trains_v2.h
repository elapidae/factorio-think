#pragma once

#include "blueprint_book.h"

//=======================================================================================
class PR_Trains_V2
{
public:
    static BluePrint_Book build();

    static BluePrint receive_1L_6_wooden_chests( Item item );

private:
    static BluePrint  send_mine_6( Item item );
    static QByteArray send_mine_6_iron_template();

    static BluePrint  send_mine_12( Item item );
    static QByteArray send_mine_12_iron_template();
};
//=======================================================================================
