#ifndef CITY_BLOCKS_H
#define CITY_BLOCKS_H

#include "blueprint.h"

//=======================================================================================
class City_Blocks
{
public:
    static BluePrint Nine_dronstations();

    static BluePrint A_rails();
    static BluePrint B_rails_one_side_directions();
    static BluePrint M_rails_between_lines();
    static BluePrint O_rails_for_endpoints();

    //static BluePrint OLeft_rails_for_endpoints();
    //static BluePrint ORight_rails_for_endpoints();
};
//=======================================================================================

#endif // CITY_BLOCKS_H
