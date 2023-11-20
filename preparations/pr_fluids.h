#pragma once

#include "blueprint_book.h"

//=======================================================================================
class PR_Fluids
{
public:
    static Blueprint_Book build();

private:
    static BluePrint send( Item item );
    static BluePrint receive( Item item );
    static QByteArray send_oil_template();
    static QByteArray receive_oil_template();
};
//=======================================================================================
