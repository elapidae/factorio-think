#include "oil_refinery.h"

#include "raw_oil_refinery.h"

//=======================================================================================
BluePrint Oil_Refinery::basic_oil_processing_1pcs()
{
    auto res = BluePrint::do_import( raw_basic_oil_processing_1pcs );
    res.icons.clear();
    res.icons.set( 1, "oil-refinery" );
    res.icons.set( 2, Item::Named::petroleum_gas() );
//    res.icons.set( 3, "signal-B" );
//    res.icons.set( 4, Item::Named::heavy_oil() );
    return res;
}
//=======================================================================================
BluePrint Oil_Refinery::advanced_oil_processing_1pcs()
{
    auto res = BluePrint::do_import( raw_advanced_oil_processing_1pcs );
    res.icons.clear();
    res.icons.set( 1, "oil-refinery" );
    res.icons.set( 2, Item::Named::petroleum_gas() );
    res.icons.set( 3, Item::Named::light_oil() );
    res.icons.set( 4, Item::Named::heavy_oil() );
    return res;
}
//=======================================================================================
BluePrint Oil_Refinery::coal_liquefaction_1pcs()
{
    auto res = BluePrint::do_import( raw_coal_liquefaction_1pcs );
    res.icons.clear();
    res.icons.set( 1, "oil-refinery" );
    res.icons.set( 2, Item::Named::heavy_oil() );
    res.icons.set( 3, "coal" );
    res.icons.set( 4, "coal" );
    return res;
}
//=======================================================================================
BluePrint Oil_Refinery::heavy_light_oil_cracking_1pcs()
{
    auto res = BluePrint::do_import( raw_heavy_light_oil_cracking_1pcs );
    res.icons.clear();
    res.icons.set( 1, "chemical-plant" );
    res.icons.set( 2, Item::Named::heavy_oil() );
    res.icons.set( 3, Item::Named::light_oil() );
    res.icons.set( 4, Item::Named::petroleum_gas() );
    return res;
}
//=======================================================================================


//=======================================================================================
BluePrint Oil_Refinery::primary_little_plant()
{
    auto res = BluePrint::do_import( raw_primary_little_plant );
    res.icons.clear();
    res.icons.set( 1, "signal-P" );
    res.icons.set( 2, "signal-1" );
    res.icons.set( 3, "plastic-bar" );
    res.icons.set( 4, "battery" );
    return res;
}
//=======================================================================================
BluePrint Oil_Refinery::advanced_long_build_right_v0()
{
    auto res = BluePrint::do_import( raw_advanced_long_build_right_v0 );
    res.icons.clear();
    res.icons.set( 1, "signal-R" );
    res.icons.set( 2, "signal-0" );
    res.icons.set( 3, "oil-refinery" );
    res.icons.set( 4, "chemical-plant" );
    return res;
}
//=======================================================================================
BluePrint Oil_Refinery::advanced_long_build_left_v0()
{
    auto res = BluePrint::do_import( raw_advanced_long_build_left_v0 );
    res.icons.clear();
    res.icons.set( 1, "signal-L" );
    res.icons.set( 2, "signal-0" );
    res.icons.set( 3, "oil-refinery" );
    res.icons.set( 4, "chemical-plant" );
    return res;
}
//=======================================================================================
BluePrint Oil_Refinery::advanced_short_build_right_v1()
{
    auto res = BluePrint::do_import( raw_advanced_short_build_right_v1 );
    res.icons.clear();
    res.icons.set( 1, "oil-refinery" );
    res.icons.set( 2, "chemical-plant" );
    res.icons.set( 3, Item::Named::light_oil() );
    res.icons.set( 4, Item::Named::heavy_oil() );
    return res;
}
//=======================================================================================
BluePrint Oil_Refinery::cliff_explosives()
{
    auto res = BluePrint::do_import( raw_cliff_explosives );
    res.icons.set( 1, "cliff-explosives" );
    res.icons.set( 2, "cliff-explosives" );
    res.icons.set( 3, "grenade" );
    res.icons.set( 4, "empty-barrel" );
    return res;
}
//=======================================================================================


//=======================================================================================
BluePrint_Book Oil_Refinery::book()
{
    BluePrint_Book res;
    res.icons.set( 1, "oil-refinery" );

    res.add( basic_oil_processing_1pcs() );
    res.add( advanced_oil_processing_1pcs() );
    res.add( coal_liquefaction_1pcs() );
    res.shift_to(4);
    res.add( heavy_light_oil_cracking_1pcs() );
    res.next_line();

    res.add( advanced_short_build_right_v1() );
    res.shift_to(2);
    res.add( advanced_long_build_left_v0() );
    res.add( advanced_long_build_right_v0() );
    res.next_line();

    res.add( primary_little_plant() );
    res.add( cliff_explosives() );

    return res;
}
//=======================================================================================
