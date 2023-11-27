#pragma once

#include "blueprint_book.h"

//=======================================================================================
class PR_Fluids
{
public:
    static Blueprint_Book build();

private:
    static QByteArray prod_second_circle();
    static QByteArray prod1_3sections();
    static QByteArray prod1_4sections();
    static QByteArray prod_stuff4();

    static QByteArray prod_stuff4_without_trains();

    static BluePrint send( Item item );
    static BluePrint receive( Item item );
    static QByteArray send_oil_template();
    static QByteArray receive_oil_template();
};
//=======================================================================================
