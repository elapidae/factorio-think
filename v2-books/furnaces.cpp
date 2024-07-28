#include "furnaces.h"

#include "vlog.h"
#include "raw_furnances.h"
#include "items/decider_combinator.h"
#include "items/chests.h"

//=======================================================================================
BluePrint Furnances::steel_furnance_plant_L1_24pcs()
{
    return BluePrint::do_import( raw_steel_furnance_plant_L1_24pcs );
}
//=======================================================================================
BluePrint Furnances::steel_furnance_plant_L2_24pcs()
{
    return BluePrint::do_import( raw_steel_furnance_plant_L2_24pcs );
}
//=======================================================================================
static BluePrint copper_tier1_replace( Item from, Item to )
{
    static auto tmpl_ore = Item::Named::copper_ore();
    static auto tmpl_plate = Item::Named::copper_plate();
    static auto _bp = BluePrint::do_import( raw_copper_tier1_trainplant );
    auto res = _bp;

    res.icons.replace_all( tmpl_plate, to );
    res.icons.replace_all( tmpl_ore, from );

    res.train_stops_replace( tmpl_plate, to );
    res.train_stops_replace( tmpl_ore, from );

    res.constant_combinators_replace( tmpl_plate, to );
    res.constant_combinators_replace( tmpl_ore, from );

    auto to_count = to.stack_size * 40; // one waggon
    res.decider_combinators_replace_first_signal_count( tmpl_plate, to, to_count );

    auto from_count = from.stack_size * 8 * 6;
    res.decider_combinators_replace_first_signal_count( tmpl_ore, from, from_count );

    res.schedules.replace( 0, tmpl_ore, from );
    res.schedules.replace( 0, tmpl_plate, to );

    // Need to clear trains from fuel:
    res.locomotives_init_fuel_coal(0);

    auto chests = res.find(Item::get("logistic-chest-requester"));
    for ( auto && ch: chests )
    {
        auto obj = ch.toObject();
        {
            auto arr = obj["request_filters"].toArray();
            {
                auto filter = arr.at(0).toObject();
                filter["name"] = "nuclear-fuel";
                arr[0] = filter;
            }
            obj["request_filters"] = arr;
        }
        ch = obj;
    }
    return res;
}
//=======================================================================================
BluePrint_Book Furnances::SteelFurnances_TrainPlant_Tier1()
{
    auto fn = copper_tier1_replace;

    BluePrint_Book res;

    // for inserter templates.
    res.next_line();

    res.add( fn(Item::Named::copper_ore(), Item::Named::copper_plate()) );
    res.add( fn(Item::Named::iron_ore(), Item::Named::iron_plate()) );
    res.add( fn(Item::Named::iron_plate(), Item::Named::steel_plate()) );
    res.next_line();

    return res;
}
//=======================================================================================


//=======================================================================================
static BluePrint electric_furnance_v2( Item from, Item to )
{
    static auto ore   = Item::Named::copper_ore();
    static auto plate = Item::Named::copper_plate();
    static auto tmpl  = BluePrint::do_import( raw_Plant_Copper_ElectricFurnance_v2 );

    auto res = tmpl;

    // first is electric furnance, second -- train station.
    res.icons.set( 1, Item::get("electric-furnace") );
    res.icons.set( 2, Item::get("train-stop") );
    res.icons.set( 3, from );
    res.icons.set( 4, to );

    res.train_stops_replace( plate, to );
    res.train_stops_replace( ore, from );

    // schedules
    res.schedules.replace( 0, ore, from );
    res.schedules.replace( 0, plate, to );

    res.constant_combinators_replace( plate, to );
    res.constant_combinators_replace( ore, from );

    auto to_count = to.stack_size * 40; // one waggon
    res.decider_combinators_replace_first_signal_count( plate, to, to_count );

    auto from_count = from.stack_size * 8 * 6;
    res.decider_combinators_replace_first_signal_count( ore, from, from_count );

    return res;
}
//---------------------------------------------------------------------------------------
BluePrint_Book Furnances::ElectricFurnances_TrainPlant_Tier2()
{
    auto fn = electric_furnance_v2;

    BluePrint_Book res;
    res.icons.set( 1, "electric-furnace" );
    res.icons.set( 2, "train-stop" );
    res.icons.set( 3, "signal-V" );
    res.icons.set( 4, "signal-2" );

    res.add( fn(Item::Named::copper_ore(), Item::Named::copper_plate()) );
    res.add( fn(Item::Named::iron_ore(),   Item::Named::iron_plate())   );
    res.add( fn(Item::Named::iron_plate(), Item::Named::steel_plate())  );
    res.next_line();

    return res;
}
//=======================================================================================
// With full beacons.
static BluePrint electric_furnance_v3( Item from, Item to )
{
    static auto ore   = Item::Named::copper_ore();
    static auto plate = Item::Named::copper_plate();
    static auto tmpl  = BluePrint::do_import( raw_copper_plant3 );
    auto res = tmpl;

    // first is electric furnance, second -- train station.
    res.icons.set( 1, Item::get("train-stop") );
    res.icons.set( 2, Item::get("speed-module-3") );
    res.icons.set( 3, from );
    res.icons.set( 4, to );

    res.train_stops_replace( plate, to );
    res.train_stops_replace( ore, from );

    // schedules
    res.schedules.replace( 0, ore, from );
    res.schedules.replace( 0, plate, to );

    res.constant_combinators_replace( plate, to );
    res.constant_combinators_replace( ore, from );

    // dc -----------
    auto from_count = from.stack_size * 8 * 6; // 6 chests, by 8 cells (1/2 wooden chest)
    auto to_count = to.stack_size * 40;        // one waggon
    auto deciders = res.find_decider_combinators();
    for ( auto ref: deciders )
    {
        Decider_Combinator2 dc( ref );
        if ( dc.is_train_stop_controller() )
        {
            if ( dc.first_signal_name() == ore.name )
            {
                dc.replace_first_signal_count( ore, from, from_count );
                continue;
            }
            if ( dc.first_signal_name() == plate.name )
            {
                dc.replace_first_signal_count( plate, to, to_count );
                continue;
            }
            qdeb << ref;
            throw;
        }
        auto is = dc.correct_if_filter( ore, from );
        if ( is )
        {
            continue;
        }

        if ( dc.first_signal_name() == "train-stop" )
            continue;

        if ( dc.first_signal_name() == ore.name &&
             dc.output_signal_name() == "signal-P"
           )
        {
            dc.first_signal( from );
            continue;
        }
        qdeb << ref; throw;
    } // for each dc
    //---------------

    return res;
}
BluePrint_Book Furnances::electricFurnances_trainPlant_Tier3()
{
    auto fn = electric_furnance_v3;

    BluePrint_Book res;
    res.icons.set( 2, "train-stop" );
    res.icons.set( 1, "speed-module-3" );
    res.icons.set( 3, "signal-V" );
    res.icons.set( 4, "signal-3" );

    res.add( fn(Item::Named::copper_ore(), Item::Named::copper_plate()) );
    res.add( fn(Item::Named::iron_ore(),   Item::Named::iron_plate())   );
    res.add( fn(Item::Named::iron_plate(), Item::Named::steel_plate())  );
    res.next_line();

    return res;
}
//=======================================================================================
BluePrint_Book Furnances::tier0123()
{
    BluePrint_Book res;
    res.icons.set( 1, "stone-furnace" );
    res.icons.set( 2, "steel-furnace" );
    res.icons.set( 3, "electric-furnace" );
    res.icons.set( 4, "speed-module-3" );

    res.add( steel_furnance_plant_L1_24pcs() );
    res.add( steel_furnance_plant_L2_24pcs() );
    res.add( SteelFurnances_TrainPlant_Tier1() );
    res.add( ElectricFurnances_TrainPlant_Tier2() );
    res.add( electricFurnances_trainPlant_Tier3() );

    return res;
}
//=======================================================================================
