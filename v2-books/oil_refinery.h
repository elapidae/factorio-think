#ifndef OIL_REFINERY_H
#define OIL_REFINERY_H

#include "blueprint_book.h"

//=======================================================================================
class Oil_Refinery
{
public:
    static BluePrint basic_oil_processing_1pcs();
    static BluePrint advanced_oil_processing_1pcs();
    static BluePrint coal_liquefaction_1pcs();
    static BluePrint heavy_light_oil_cracking_1pcs();

    static BluePrint advanced_short_build_right_v1();
    static BluePrint advanced_long_build_right_v0();
    static BluePrint advanced_long_build_left_v0();

    static BluePrint primary_little_plant();
    static BluePrint cliff_explosives();

    static BluePrint_Book book();
};
//=======================================================================================

#endif // OIL_REFINERY_H
