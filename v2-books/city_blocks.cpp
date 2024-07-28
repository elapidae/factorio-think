#include "city_blocks.h"

#include "blueprint_io.h"
#include "bprint_landfill.h"
#include "qdeb.h"

#include "raw_city_blocks.h"

//=======================================================================================
BluePrint City_Blocks::A_rails()
{
    return BluePrint::do_import( raw_A_rails_bp );
}
//=======================================================================================
BluePrint City_Blocks::B_rails_one_side_directions()
{
    return BluePrint::do_import( raw_B_rails );
}
//=======================================================================================
BluePrint City_Blocks::M_rails_between_lines()
{
    return BluePrint::do_import( raw_M_rails );
}
//=======================================================================================
BluePrint City_Blocks::O_rails_for_endpoints()
{
    return BluePrint::do_import( raw_O_rails_for_endpoints_bp );
}
//=======================================================================================
BluePrint City_Blocks::assemble_block()
{
    return BluePrint::do_import( raw_assemble_block );
}
//=======================================================================================
BluePrint City_Blocks::city_assemblies()
{
    return BluePrint::do_import( raw_city_assemblies );
}
//=======================================================================================
BluePrint City_Blocks::Nine_dronstations()
{
    return BluePrint::do_import( raw_nine_dronstations );
}
//=======================================================================================
BluePrint City_Blocks::Nine_dronstations_with_intermediate_blocks()
{
    return BluePrint::do_import( raw_nine_dronstations_with_intermediate_blocks );
}
//=======================================================================================
BluePrint_Book City_Blocks::book()
{
    BluePrint_Book res;
    res.icons.set( 1, Item::virtual_signal("C") );
    res.icons.set( 2, Item::virtual_signal("I") );
    res.icons.set( 3, Item::virtual_signal("T") );
    res.icons.set( 4, Item::virtual_signal("Y") );

    res.add( Nine_dronstations() );
    res.add( Nine_dronstations_with_intermediate_blocks() );
    res.next_line();
    res.add( A_rails() );
    res.add( B_rails_one_side_directions() );
    res.add( M_rails_between_lines() );
    res.add( O_rails_for_endpoints() );
    res.next_line();

    res.add( assemble_block() );
    res.add( city_assemblies() );

    return res;
}
//=======================================================================================
