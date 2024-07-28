#ifndef FURNANCES_H
#define FURNANCES_H

#include "blueprint_book.h"

//=======================================================================================
class Furnances
{
public:
    // Steel furnances with two modifiers:
    //  - the first is easier for handle.
    //  - the second -- compacted for drods.
    static BluePrint steel_furnance_plant_L1_24pcs();
    static BluePrint steel_furnance_plant_L2_24pcs();

    static BluePrint_Book SteelFurnances_TrainPlant_Tier1();

    static BluePrint_Book ElectricFurnances_TrainPlant_Tier2();

    // With Beacons, much productive as possible.
    static BluePrint_Book electricFurnances_trainPlant_Tier3();

    static BluePrint_Book tier0123();
};
//=======================================================================================


#endif // FURNANCES_H
