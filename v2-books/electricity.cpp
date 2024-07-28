#include "electricity.h"

#include "raw_electricity.h"

//=======================================================================================
BluePrint Electricity::first_nuclear_x3()
{
    return BluePrint::do_import( raw_first_nuclear_x3 );
}
//=======================================================================================
BluePrint Electricity::L0_electric_station_40pcs()
{
    return BluePrint::do_import( raw_burning_station_40pcs );
}
//=======================================================================================
BluePrint Electricity::accumulator_block()
{
    return BluePrint::do_import( raw_accumulator_block );
}
//=======================================================================================
BluePrint Electricity::solar_panel_block()
{
    return BluePrint::do_import( raw_solar_panel_block );
}
//=======================================================================================
BluePrint_Book Electricity::tier1()
{
    BluePrint_Book res;

    res.icons.set( 1, Item::get("steam-engine") );
    res.icons.set( 2, Item::get("accumulator") );
    res.icons.set( 3, Item::get("solar-panel") );
    res.icons.set( 4, Item::get("nuclear-reactor") );

    res.add( L0_electric_station_40pcs() );
    res.add( accumulator_block() );
    res.add( solar_panel_block() );
    res.add( first_nuclear_x3() );

    return res;
}
//=======================================================================================
