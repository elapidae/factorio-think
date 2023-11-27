#ifndef PR_BURN_PROD_GREEN_AS_IS_H
#define PR_BURN_PROD_GREEN_AS_IS_H

#include "blueprint_book.h"

class PR_Burn_Prod_Green_AS_IS
{
public:
    static Blueprint_Book build();

    static BluePrint coal_prod( Item from, Item to );
    static QByteArray coal_prod_copper();

    static QByteArray tmpl();
};

#endif // PR_BURN_PROD_GREEN_AS_IS_H
