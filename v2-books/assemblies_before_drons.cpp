#include "assemblies_before_drons.h"

#include "items/chests.h"
#include "items/assembling_machine.h"
#include "items/constant_combinator.h"
#include "items/inserter.h"
#include "recipe.h"

//=======================================================================================
// Ass2 machine
// CComb "C" for count;
// CComb "R" for recipe;
// storage chest as replacer, right to wooden chest;
static auto raw_ass2_R_C_wooden_storage = R"(0eNqtVF1vozAQ/C/7DFWg+UR9u39wj62iyDhbspKxkb2
kjSL++62NDkUninqne0HY7MzOzGLfoTY9dp4sQ3UH0s4GqN7uEKixysQ9vnUIFRBjCxlY1caVCgHb2pBt8lbpC1nM
SxgyIHvGT6iKIZuhuJLnXnYmlrEif31AlsMxA7RMTDgqSYvbyfZtjV6oJ3TUyspyrl1bk1XsvFB3LgjW2dg38m0OT
5sMbvFt97SRRgJj78ypxou6kmCk8J0Mo//C+Veyf0Ji62N0xYP14xDd/yG7XI5uRvd+0n1Iuj1qSnpCq4zJ0aBmTz
rvnEGY6fj8z0Fti/8b1I+/CWo9ockG9NJtMZwFrZq87olP8u08od/JBz59Wzpe0d9YhtSMHsYgRWUZV22nfEqzghc
YxgIrY6F0iu5QxEfjEe3jn0xnqLbR/Iz7zSTAuIYCy3z1BQPnQdqoBpfnVkoWM6TbifTDuTPakXI51vJ3rN/zs05+
5Oima6J6uFUykAhDalLui/XuUO7228PqebUehl+9ZoDD)";
static auto prepare_recipe_ass2( Item item, int count )
{
    static auto BP = BluePrint::do_import( raw_ass2_R_C_wooden_storage );
    auto res = BP;

    res.icons.set( 1, item );
    res.icons.set( 2, "assembling-machine-2" );
    res.icons.set( 3, "wooden-chest" );
    res.icons.set( 4, Chests::chest_storage() );

    {
        auto am = res.find_assembling_machines().at(0);
        Assembling_Machine::set_recipe( am, item );
    }

    {
        auto ins = res.find("inserter").at(0);
        Inserter i( ins.toObject() );
        i.control_behavior().circuit_condition_constant( count );
        ins = i.obj;
    }

    {
        auto ccombs = res.find( Constant_Combinator::name );
        auto cc_recipe = Constant_CombinatorRef::find( ccombs, "signal-R" );
        auto recipe = Recipe::get( item.name );
        cc_recipe.save_recipe( recipe );

        auto cc_count = Constant_CombinatorRef::find( ccombs, "signal-C" );
        cc_count.clear_behavior();
        auto cstr = QString("%1").arg(count);
        int idx = 1;
        if ( cstr.size() < 4 ) // if we have place, can put a picture
            cc_count.set_behavior( idx++, item, recipe.amount );
        if ( cstr.size() <= 2 ) // the second as upper line in cc.
            cc_count.set_behavior( idx++, item, recipe.amount );

        for ( auto ch: cstr )
            cc_count.set_behavior( idx++, QString("signal-") + ch, 0 );
    }

    return res;
}
//=======================================================================================
BluePrint Assemblies_Before_Drons::yellow_belts()
{
    BluePrint res;
    throw;
    return res;
}
//=======================================================================================
BluePrint_Book Assemblies_Before_Drons::book()
{
    BluePrint_Book res;
    res.add( yellow_belts() );
    return res;
}
//=======================================================================================
BluePrint_Book Assemblies_Before_Drons::templates()
{
    BluePrint_Book res;
    auto fn = prepare_recipe_ass2;

    res.icons.set( 1, "assembling-machine-2" );
    res.icons.set( 2, "wooden-chest" );
    res.icons.set( 3, "signal-T" );
    res.icons.set( 4, "signal-T" );
    //-----------------------------------------

//    res.add( fn("electric-mining-drill", 50) );
//    res.add( fn("assembling-machine-1", 50) );
//    res.add( fn("assembling-machine-2", 50) );
//    res.add( fn("assembling-machine-3", 50) );
//    res.add( fn("lab", 1) );
//    res.next_line();

//    res.add( fn("repair-pack", 100) );
//    res.add( fn("radar", 10) );
//    res.add( fn("gun-turret", 25) );
//    res.add( fn("firearm-magazine", 2000) );
//    res.add( fn("piercing-rounds-magazine", 2000) );
    res.add( fn("laser-turret", 50) );
    res.next_line();

//    res.add( fn("transport-belt", 500) );
//    res.add( fn("underground-belt", 100) );
//    res.add( fn("splitter", 50) );
//    res.next_line();

//    res.add( fn("inserter", 50) );
//    res.add( fn("long-handed-inserter", 50) );
//    res.add( fn("fast-inserter", 50) );
//    res.next_line();

//    res.add( fn("medium-electric-pole", 100) );
//    res.add( fn("iron-stick", 0) );
//    res.add( fn("big-electric-pole", 100) );
//    res.next_line();

//    res.add( fn("stone-furnace", 12) );
//    res.add( fn("steel-furnace", 24) );
//    res.add( fn("boiler", 2) );
//    res.add( fn("steam-engine", 4) );
//    res.next_line();

    res.add( fn("train-stop", 8) );
    res.add( fn("iron-stick", 8) );
    res.add( fn("rail", 1000) );
    res.next_line();

    res.add( fn("locomotive", 10) );
    res.add( fn("engine-unit", 0) );
    res.add( fn("pump", 10) );
    res.next_line();

    res.add( fn("pipe", 100) );
    res.add( fn("pipe-to-ground", 100) );
    res.add( fn("offshore-pump", 10) );
    res.add( fn("pumpjack", 10) );
    res.add( fn("oil-refinery", 2) );
    res.add( fn("chemical-plant", 4) );

    res.add( fn("rail-signal", 50) );
    res.add( fn("rail-chain-signal", 50) );
    res.add( fn("cargo-wagon", 4) );
    res.add( fn("fluid-wagon", 4) );
    res.add( fn("storage-tank", 10) );

    res.add( fn("cliff-explosives", 99) );
    res.add( fn("empty-barrel", 3) );
    res.add( fn("grenade", 3) );

    //res.add( fn("automation-science-pack", -1) );
    //res.add( fn("automation-science-pack", 1) );
    //res.add( fn("logistic-science-pack", 1) );
    //res.add( fn("chemical-science-pack", 1) );
    //res.add( fn("war-science-pack", 1) );
    res.next_line();

    return res;
}
//=======================================================================================
