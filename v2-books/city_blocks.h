#ifndef CITY_BLOCKS_H
#define CITY_BLOCKS_H

#include "blueprint_book.h"

//=======================================================================================
class City_Blocks
{
public:
    static BluePrint Nine_dronstations();
    static BluePrint Nine_dronstations_with_intermediate_blocks();

    static BluePrint A_rails();
    static BluePrint B_rails_one_side_directions();
    static BluePrint M_rails_between_lines();
    static BluePrint O_rails_for_endpoints();

    static BluePrint assemble_block();

    static BluePrint city_assemblies();

    static BluePrint_Book book();
};
//=======================================================================================

#endif // CITY_BLOCKS_H
