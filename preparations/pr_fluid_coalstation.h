#ifndef PR_FLUID_COALSTATION_H
#define PR_FLUID_COALSTATION_H

#include "blueprint_book.h"

class PR_Fluid_CoalStation
{
public:
    static BluePrint_Book rs_pairs(); // 3 pcs

private:
    static BluePrint rs_pair( Item fluid );
    static QByteArray rs_pair_heavy_oil();
};

#endif // PR_FLUID_COALSTATION_H
