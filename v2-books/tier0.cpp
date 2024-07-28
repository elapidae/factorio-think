#include "tier0.h"

#include "vlog.h"
#include "qdeb.h"
#include "items/inserter.h"
#include "items/chests.h"
#include "items/constant_combinator.h"
#include "city_blocks.h"
#include "furnaces.h"
#include "items/assembling_machine.h"
#include "assemble/recipe_maker.h"
#include "electricity.h"
#include "train_stations.h"

//====================
#include "raw_tier0.h"
//====================

#include <iostream>
using std::cout;

Item rome_label( int count )
{
    if ( count ==   1 ) return Item::virtual_signal( "I" );
    if ( count ==   5 ) return Item::virtual_signal( "V" );
    if ( count ==  10 ) return Item::virtual_signal( "X" );
    if ( count ==  50 ) return Item::virtual_signal( "L" );
    if ( count == 100 ) return Item::virtual_signal( "C" );
    if ( count == 500 ) return Item::virtual_signal( "D" );
    throw verror;
}

//=======================================================================================
static auto storage_chest_n_inserter = R"(0eNqVUtuKg0AM/Zc8a6na28r+yVJktKkNjBl3ZpRK8d83o7QrdGnZFyFOcm7JDUrdYWuJPeQ3oMqwg/zrBo5qVjr880OLkAN5bCACVk2otKnJeari6oLOx84bq2qEMQLiE14hT8boLUgg84p9XJmmJFYCskBIx2MEyJ484axpKoaCu6ZEKxTv1ETQGifjhoMEgczS1TaCAfL9aitEws9YhXcXGpLwqS0iL9noJHPjcZR+i9+d4Bdn0h7trOlu96EFr60W1h7jziqmrokrxWw4dhfUGgJrF8JeC2b05Cl9Gc6zoWxh6A+47AFH7NCK6heh7O6heGt0UeJF9SSk0lWRrTryhbydHqNnspLF04p7sr5T+nfLc0eMPdrBX4hrmFkmd5JcGqqmVXaymMMnjP/ZTRJ2E05luq18cc8RCKWb1KaHZLP/SPeH3cc6W2/G8QcocANq)";
static BluePrint chest_inserter( Item chest, Item inserter, int count )
{
    static auto BP = BluePrint::do_import( storage_chest_n_inserter );
    auto res = BP;
    auto label = rome_label( count );

    res.icons.set( 1, chest );
    res.icons.set( 2, inserter );
    res.icons.set( 3, label );
    res.icons.set( 4, Item::get("green-wire") );

    // Combinator
    auto cc_ref = res.find_unique( Constant_Combinator::get() );
    Constant_Combinator cc{ cc_ref.toObject() };
    cc.set_behavior( 1, label, 0 );
    cc_ref = cc.obj;

    // Chest
    auto ch_ref = res.find_unique( Chests::chest_storage() );
    auto ch_obj = ch_ref.toObject();
    ch_obj["name"] = chest.name;
    ch_ref = ch_obj;

    // Inserter
    auto ins_ref = res.find_unique( Inserter::it_inserter() );
    auto ins_obj = ins_ref.toObject();
    ins_obj["name"] = inserter.name;
    {
        auto control_behavior = ins_obj["control_behavior"].toObject();
        {
            auto circuit_condition = control_behavior["circuit_condition"].toObject();
            circuit_condition["constant"] = count;
            control_behavior["circuit_condition"] = circuit_condition;
        }
        ins_obj["control_behavior"] = control_behavior;
    }
    ins_ref = ins_obj;

    return res;
}
//=======================================================================================
BluePrint_Book Tier0::out_chests_with_size_controls()
{
    BluePrint_Book res;

    res.icons.set( 1, Chests::chest_storage() );
    res.icons.set( 2, Inserter::it_inserter() );
    res.icons.set( 3, Constant_Combinator::get() );
    res.icons.set( 4, Item::get("green-wire") );

    auto counts = { 1, 5, 10, 50, 100, 500 };
    auto chests = {
        Chests::wooden_chest(),
        Chests::chest_storage(),
        Chests::chest_passive_provider(),
    };
    auto inserters = {
        //Inserter::it_burner_inserter(),
        Inserter::it_inserter(),
        Inserter::it_fast_inserter(),
    };
    for ( auto chest: chests )
    {
        for ( auto inserter: inserters )
        {
            for ( auto count: counts )
            {
                res.add( chest_inserter(chest, inserter, count) );
            }
        }
        //res.next_line();
    }
    return res;
}
//=======================================================================================
BluePrint_Book Tier0::couples_around_small_poles()
{
    return BluePrint_Book::do_import( raw_T0_A1_couples_around_small_poles );
}
//=======================================================================================
BluePrint Tier0::five_labs()
{
    return BluePrint::do_import( raw_science_five_labs );
}
//=======================================================================================
BluePrint_Book Tier0::tier0_book()
{
    BluePrint_Book res;
    res.icons.set( 1, Item::Named::assembling_machine_1() );
    res.icons.set( 2, Item::get("burner-mining-drill") );
    res.icons.set( 3, Item::virtual_signal("T") );
    res.icons.set( 4, Item::virtual_signal("0") );

    res.add( City_Blocks::book() );
    res.add( out_chests_with_size_controls() );
    res.add( first_recipies() );
    res.add( couples_around_small_poles() );
    res.next_line();

    res.add( Electricity::tier1() );
    res.add( Furnances::tier0123() );
    res.next_line();

    res.add( Train_Stations::R_solid_intermediate_stops() );
    res.add( Train_Stations::S_solid_intermediate_stops() );
    res.add( Train_Stations::RS_fluid_intermediate_stops() );
    res.next_line();

    res.add( five_labs() );

    return res;
}
//=======================================================================================
BluePrint_Book Tier0::first_recipies()
{
    BluePrint_Book res;
    res.icons.set( 1, Item::Named::assembling_machine_1() );
    res.icons.set( 2, Item::get("steam-engine") );
    res.icons.set( 3, Item::virtual_signal("T") );
    res.icons.set( 4, Item::virtual_signal("0") );

    auto item = &Item::get;
    auto ass1 = &Recipe_Maker::A1_assemble_with_recipe;
    auto without = &Recipe_Maker::A1_assemble_without_recipe;

    res.add( without(   1, "I") );
    res.add( without(   5, "V") );
    res.add( without(  10, "X") );
    res.add( without(  50, "L") );
    res.add( without( 100, "C") );
    res.add( without( 500, "M") );
    // six, not next line.

    {
        res.add( ass1( item("iron-gear-wheel"), 100) );
        res.add( ass1( item("copper-cable"), 200) );
        res.add( ass1( item("electronic-circuit"), 200) );
    }
    res.next_line();
    {
        res.add( ass1( item("wooden-chest"), 48) );
        res.add( ass1( item("small-lamp"), 40) );
        res.add( ass1( item("small-electric-pole"), 40) );
        res.add( ass1( item("medium-electric-pole"), 100) );
        res.add( ass1( item("iron-stick"), 0) );
        res.add( ass1( item("big-electric-pole"), 100) );
    }
    res.next_line();
    {
        auto pipe = "pipe";
        auto pipe_to_ground = "pipe-to-ground";
        auto offshore_pump = "offshore-pump";
        res.add( ass1( item(pipe), 40) );
        res.add( ass1( item(pipe_to_ground), 50) );
        res.add( ass1( item(offshore_pump), 1) );
    }
    res.next_line();
    {
        auto boiler = "boiler";
        auto steam_engine = "steam-engine";
        auto stone_furnace = "stone-furnace";
        auto steel_furnace = "steel-furnace";
        res.add( ass1( item(boiler), 2) );
        res.add( ass1( item(steam_engine), 4) );
        res.add( ass1( item(stone_furnace), 6) );
        res.add( ass1( item(steel_furnace), 6) );
    }
    res.next_line();
    {
        auto transport_belt = "transport-belt";
        auto underground_belt = "underground-belt";
        auto splitter = "splitter";
        res.add( ass1( item(transport_belt), 300) );
        res.add( ass1( item(underground_belt), 40) );
        res.add( ass1( item(splitter), 30) );
    }
    res.next_line();
    {
        auto burner_inserter = "burner-inserter";
        auto inserter = "inserter";
        auto long_handed_inserter = "long-handed-inserter";
        auto fast_inserter = "fast-inserter";
        res.add( ass1( item(burner_inserter), 2) );
        res.add( ass1( item(inserter), 50) );
        res.add( ass1( item(long_handed_inserter), 50) );
        res.add( ass1( item(fast_inserter), 50) );
    }
    res.next_line();
    {
        auto electric_mining_drill = "electric-mining-drill";
        auto assembling_machine_1 = "assembling-machine-1";
        auto assembling_machine_2 = "assembling-machine-2";
        res.add( ass1( item(electric_mining_drill), 20) );
        res.add( ass1( item(assembling_machine_1), 10) );
        res.add( ass1( item(assembling_machine_2), 10) );
    }
    res.next_line();
    {
        auto lab = "lab";
        auto automation_science_pack = "automation-science-pack";
        res.add( ass1( item(lab), 1) );
        res.add( ass1( item(automation_science_pack), 200) );
    }
    res.next_line();
    {
        res.add( ass1( item("firearm-magazine"), 400) );
        res.add( ass1( item("piercing-rounds-magazine"), 800) );
        res.add( ass1( item("gun-turret"), 10) );
        res.add( ass1( item("laser-turret"), 150) );
        res.add( ass1( item("radar"), 5) );
        res.add( ass1( item("repair-pack"), 100) );
    }
    return res;
}
//auto bp = BluePrint::do_import( raw_tier0_assemble1_list );
//auto ams = bp.find_assembling_machines();
//for ( auto am: ams)
//{
//    auto r = Assembling_Machine{am.toObject()}.recipe().name;
//    auto n = r;
//    n.replace('-', '_');
//    cout << "    auto " << n.toStdString() << " = \"" << r.toStdString() << "\";\n";
//}
//cout.flush();
//exit(00);
//=======================================================================================
