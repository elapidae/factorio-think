#pragma once

#include "blueprint_book.h"

class PR_Uran
{
public:
    static Blueprint_Book build();

private:
    static QByteArray as_is();
    static QByteArray refined_station_template();
};
