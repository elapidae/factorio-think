#pragma once

#include "blueprint_book.h"

class PR_Uran
{
public:
    static BluePrint_Book build();

    // As is -- product assemble2 line with turret
    // Need: copper, concrete, iron, steel, red plates
    static BluePrint_Book build_prod_line();

    static BluePrint_Book assemble_tmpl();

private:
    static QByteArray as_is();
    static QByteArray assemble2_as_is();

    static QByteArray refined_station_template();

    //  ass machines with reactor, turbine, etc. + turret (because of concrete)
    static QByteArray assemble2_template();
};
