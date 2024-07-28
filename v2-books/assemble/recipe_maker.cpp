#include <iostream>
#include "recipe_maker.h"

#include "qdeb.h"
#include "items/constant_combinator.h"
#include "items/assembling_machine.h"
#include "items/chests.h"
#include "items/inserter.h"

#include "raw_assembling_machines.h"
#include "raw_chests.h"

using std::cout;

//=======================================================================================
static auto assemble_template_medium_pole = R"(0eNqtlN1ugzAMhd/F11C1QP/
Q3mSqqgAutQQJS0w1hHj3JemK2Nq1W7UbpEDs75zjhB6yqsVGk2RIe6BcSQPpaw+GSikq9467BiEFYqwhAClqtxLG
YJ1VJMuwFvmRJIYRDAGQLPAd0sUQ3GhxIs2tfTN2Oe8IC8WT2mjYBYCSiQnPWvyi28u2zlDb5vdVBNAoY4uVdGjXM
IpnywA6WxmvZktL0piTV1RjQW0dYoU5a8rDRlUITvs3ZDQiK1WSYbs1P6Lh0LDSosT70K2H2milxZBPuIeFe5QaUU
49UgFpPBHg1smwG7zot9Yi9weqGPU5mUvco7ybhhy7dQOe207X5uKxmqRBbZvft7O52GGtqn2GR3Eipd3GnHTeEu/
tt2KsPpC2qn99GITs2E6yhDPDsPDK3aJuhBbsUPACw18ijVyEN6wnI/2CCi0mI+kxN1JIrod6lcJ0QA+u0Q/n7zKv
cDG5Ubv/MLx83vDmOcMPLv2n069G3R/AB5VOfk8BnCzEa4s2i2S9jdab1XYez5Nh+ADMAJzH)";
//---------------------------------------------------------------------------------------
static auto assemble_medium_pole_with_manipulators = R"(0eNrdVtuOozAM/Rc/k1VLKbRo/2Q1QgE8
1BIENgnVVhX/vk7QIIYy1dxepi8I5+JziTG5Ql732GlSFtIrUNEqA+mfKxiqlKzdmL10CCmQxQYCULJxkTQGm7wmV
YlGFidSKEIYAiBV4j9It8NTAKgsWcIxnw8umeqbHDUvuJ8pgK41vLlVjgEn3G2iX/sALrwz4TdG0liQJ9ZgSX0js
MbCaipE19bIVG4gwwmybhnsJJlqKUgZ1JbnVyB3E2ToIdkcq9s6y/Ekz9Rqt7AgXfRkM54rp93PpI3Nbiw8k7Y9j0
xExhVCqotl4RWMGMZKdxobFzSd1NI6KPgNwzivWCj5c7rC1j0qjajmLlMJ6WF4GoYVG3YT+j3p0SNKj75QAYm3oSQ
9MvDJHsKU/RdMiR/VlHhCf4ESDJOT8jArnuwXhbLmwjPV7Oi72usbPY3T9k612M477XcITj4vOP6c4LfOuW
ztTOlroSvED7PyrchYNqs4obHCMHFZ4f3mNh3W+9zbzwi4OFrE4SKOF/FuER+9Jv6V/e2Zcjb360X1/ZKYfNq4Mrg
x5/jBXh//1F7Ptw3/AaWz60wAZzbTUw0P2yg5hskhPm5Y7zD8By2OD0E=)";
//---------------------------------------------------------------------------------------
static auto assemble_medium_pole_with_red_manips = R"(0eNrdltuOozAMht/
F1zAqlEOL9k1WIxTAQy1BYJNQbVXx7usEDWIpU1XTvVj1Bskktv//
y0G5QtEM2CuSBrIrUNlJDdnPK2iqpWjsP3PpETIggy14IEVrI6E1tkVDsvZbUZ5Ioh/C6AHJCn9DFozvHqA0ZAinei645HJoC1Q8Ya7UdFzjJDiv8klqVIbHPeg7zcmdtAq44H63f4s9uHBmGrzF3ImVGtU1
eYEncaZO2YklqXIgk/NYNWd/kNImv/FzJmUG/
jMLmWb4Ql4M+6lh6qGNsGh2Nmh7oYSxreAHjNO4xNI20rZyYD+1QpRLy1RBdhjfR064wRDeB7qBIZoxRA6DwpKcnx
YrGlofGxakqPT7rkHYaLl/
gnz4OuSjJzCkDkNFalLgir0ElPgJKMmrQknm7p+tfG5TkHRtNpjEq42yReGDGib60FX7xcHmsoN17QfLW/dfGE6/
bzj5nuGv1rnqzMLp30Y3hB8W27cmbRhWeUJtfM3CRY3379N5sR6jFy8E2DhaxftVnKziYBUfnSe+z38NLDlf8vp0f
X9LzJx2dhvcwDnO2ffOc/TAUv7nJ5hfHu4AZYunjQdnhumkhocgSo9hekiOO/Y7jn8AKbQTrA==)";
//---------------------------------------------------------------------------------------
static BluePrint medium_pole_dot_template()
{
    (void)assemble_template_medium_pole;
    (void)assemble_medium_pole_with_manipulators;
    (void)assemble_medium_pole_with_red_manips;

    //static auto res = BluePrint::do_import( assemble_template_medium_pole );
    //static auto res = BluePrint::do_import( assemble_medium_pole_with_manipulators );
    static auto res = BluePrint::do_import( assemble_medium_pole_with_red_manips );
    return res;
}
//=======================================================================================
// Include:
// - assembing-machine-1;
// - const-comb with RCP values for recipe;
// - const-comb with CNT values for count marker;
// - inserter to storage-chest, linked to chest;
// - for long-handed-inserters to AM1, linked to chest;
BluePrint Recipe_Maker::A1_assemble_with_recipe( Item item, int count )
{
    static auto BP = BluePrint::do_import( raw_AM1_recipe_for_first_stages );
    auto res = BP;
    res.icons.set( 1, Item::Named::assembling_machine_1() );
    res.icons.set( 2, item );
    //res.icons.set( 1, Item::Named::assembling_machine_1() );
    //res.icons.set( 1, Item::Named::assembling_machine_1() );
    auto recipe = Recipe::get( item.name );

    // -- recipe in AM1;
    Assembling_Machine::set_recipe( res.find_assembling_machines().at(0), item );

    // -- item in storage-chest;
    auto chest = res.find_unique( Chests::chest_storage() );
    Chests::Storage{chest}.filter( item );

    // -- control-behavior in each inserter;
    auto inserters = res.find_inserters();
    for ( auto ref: inserters )
    {
        auto ins = Inserter( ref.toObject() );
        auto cc = ins.control_behavior();
        cc.circuit_condition_constant( count );
        ins.control_behavior( cc );
        ref = ins.obj;
    }

    // -- recipe in ccomb;
    // -- count in ccomb;
    auto combs = res.find( Constant_Combinator::get() );
    for ( auto ref: combs )
    {
        auto cc = Constant_Combinator{ ref.toObject() };
        if ( cc.get_item(0).name == "signal-R" )
        {
            cc.save_recipe( recipe );
            ref = cc.obj;
            continue;
        }
        if ( cc.get_item(0).name == "signal-C" )
        {
            cc.clear_behavior();
            auto num = QString("%1").arg( count );
            for ( int i = 0; i < num.size(); ++i )
            {
                auto S = QString( num[i] );
                cc.set_behavior( i + 1, Item::virtual_signal(S), 0 );
            }
            ref = cc.obj;
            continue;
        }
        qdeb << cc.obj;
        throw verror;
    }

    return res;
}
//=======================================================================================
BluePrint Recipe_Maker::A1_assemble_without_recipe( int count, QString label )
{
    static auto BP = BluePrint::do_import( raw_AM1_recipe_for_first_stages );
    auto res = BP;
    res.icons.set( 1, Item::Named::assembling_machine_1() );
    res.icons.set( 2, Item::virtual_signal(label) );
    //res.icons.set( 1, Item::Named::assembling_machine_1() );
    //res.icons.set( 1, Item::Named::assembling_machine_1() );

    Assembling_Machine::clear_recipe( res.find_assembling_machines().at(0) );

    // -- control-behavior in each inserter;
    auto inserters = res.find_inserters();
    for ( auto ref: inserters )
    {
        auto ins = Inserter( ref.toObject() );
        auto cc = ins.control_behavior();
        cc.circuit_condition_constant( count );
        ins.control_behavior( cc );
        ref = ins.obj;
    }

    // -- recipe in ccomb;
    // -- count in ccomb;
    auto combs = res.find( Constant_Combinator::get() );
    for ( auto ref: combs )
    {
        auto cc = Constant_Combinator{ ref.toObject() };
        if ( cc.get_item(0).name == "signal-R" )
        {
            cc.clear_behavior();
            continue;
        }
        if ( cc.get_item(0).name == "signal-C" )
        {
            cc.clear_behavior();
            auto num = QString("%1").arg( count );
            for ( int i = 0; i < num.size(); ++i )
            {
                auto S = QString( num[i] );
                cc.set_behavior( i + 1, Item::virtual_signal(S), 0 );
            }
            ref = cc.obj;
            continue;
        }
        qdeb << cc.obj;
        throw verror;
    }
    return res;
}
//=======================================================================================
BluePrint Recipe_Maker::A2_assemble_with_recipe( Item item, int count )
{
    static auto mpole = Item::get( "medium-electric-pole" );

    auto res = medium_pole_dot_template();
    auto recipe = Recipe::get( item.name );

    // 1. replace dot to item
    res.icons.set( 2, item );

    // 2.
    auto am = res.find_assembling_machines().at(0);
    Assembling_Machine::set_recipe( am, item );

    auto combinators = res.find( Item::Named::constant_combinator() );
    if ( combinators.size() != 2 ) throw verror;
    // Have seen by debugger.
    auto CC_COUNT_IDX = 0;
    auto CC_RECIPE_IDX = 1;
    auto cc_count  = Constant_Combinator{ combinators.at(CC_COUNT_IDX).toObject()  };
    auto cc_recipe = Constant_Combinator{ combinators.at(CC_RECIPE_IDX).toObject() };
    cc_recipe.clear_behavior();
    cc_count.clear_behavior();
    cc_recipe.save_recipe( recipe );
    cc_count.set_behavior( 1, item, -count );

    combinators[CC_COUNT_IDX]  = cc_count.obj;
    combinators[CC_RECIPE_IDX] = cc_recipe.obj;

    // filter in chest
    auto chest_ref = res.find_unique( Chests::chest_storage() );
    Chests::Storage cs{ chest_ref };
    cs.filter( item );

    return res;
}
//=======================================================================================
BluePrint_Book Recipe_Maker::extracted_recipies( QByteArray raw_bp )
{
    BluePrint_Book res;
    auto fn = A2_assemble_with_recipe;

    auto bp = BluePrint::do_import( raw_bp );
    auto ams = bp.find_assembling_machines();
    for ( auto am: ams )
    {
        auto r = Assembling_Machine{am.toObject()}.recipe();
        res.add( fn(Item::get(r.name), 0) );
    }
    return res;
}
//=======================================================================================
BluePrint_Book Recipe_Maker::belt_templates()
{
    BluePrint_Book res;

    res.icons.set( 1, Item::Named::virtual_signal("T") );
    res.icons.set( 2, Item::Named::transport_belt() );
    res.icons.set( 3, Item::Named::fast_underground_belt() );
    res.icons.set( 4, Item::Named::express_splitter() );

    res.add( A2_assemble_with_recipe(Item::Named::transport_belt(), 200) );
    res.add( A2_assemble_with_recipe(Item::Named::underground_belt(), 50) );
    res.add( A2_assemble_with_recipe(Item::Named::splitter(), 50) );
    res.next_line();

    res.add( A2_assemble_with_recipe(Item::Named::fast_transport_belt(), 300) );
    res.add( A2_assemble_with_recipe(Item::Named::fast_underground_belt(), 50) );
    res.add( A2_assemble_with_recipe(Item::Named::fast_splitter(), 50) );
    res.next_line();

    res.add( A2_assemble_with_recipe(Item::Named::express_transport_belt(), 700) );
    res.add( A2_assemble_with_recipe(Item::Named::express_underground_belt(), 150) );
    res.add( A2_assemble_with_recipe(Item::Named::express_splitter(), 150) );
    res.next_line();

    return res;
}
//=======================================================================================
#include "raw_belts_l3_assemble.h"
BluePrint Recipe_Maker::L3_belts()
{
    return BluePrint::do_import( belts_L3_assemble );
}
//=======================================================================================


//=======================================================================================
BluePrint_Book Recipe_Maker::engine_templates()
{
    BluePrint_Book res;

    auto engine             = Item::get( "engine-unit" );
    auto electric_engine    = Item::get( "electric-engine-unit" );
    auto flying_robot_frame = Item::get( "flying-robot-frame" );

    res.icons.set( 1, Item::Named::virtual_signal("T") );
    res.icons.set( 2, engine );
    res.icons.set( 3, electric_engine );
    res.icons.set( 4, flying_robot_frame );

    res.add( A2_assemble_with_recipe(Item::get("pipe"), 10) );
    res.next_line();

    res.add( A2_assemble_with_recipe(engine, 10) );
    res.add( A2_assemble_with_recipe(electric_engine, 10) );
    res.add( A2_assemble_with_recipe(flying_robot_frame, 10) );
    res.next_line();

    return res;
}
//=======================================================================================
#include "raw_engine_heads.h"
BluePrint Recipe_Maker::engine_head()
{
    return BluePrint::do_import( raw_engine_head_bp );
}
//=======================================================================================
BluePrint_Book Recipe_Maker::chest_templates()
{
    BluePrint_Book res;

    res.icons.set( 1, Item::Named::virtual_signal("T") );
    res.icons.set( 2, Chests::steel_chest() );
    res.icons.set( 3, Chests::chest_storage() );
    res.icons.set( 4, Chests::chest_requester() );

    res.add( A2_assemble_with_recipe(Chests::wooden_chest(), 12) );
    res.add( A2_assemble_with_recipe(Chests::steel_chest(),  12) );
    res.next_line();

    res.add( A2_assemble_with_recipe(Chests::chest_storage(),           1) );
    res.add( A2_assemble_with_recipe(Chests::chest_passive_provider(),  1) );
    res.add( A2_assemble_with_recipe(Chests::chest_requester(),         1) );
    res.add( A2_assemble_with_recipe(Chests::chest_buffer(),            1) );
    res.add( A2_assemble_with_recipe(Chests::chest_active_provider(),   1) );
    res.next_line();

    return res;
}
//=======================================================================================
BluePrint Recipe_Maker::chests()
{
    return BluePrint::do_import( raw_chests_bp );
}
//=======================================================================================
BluePrint_Book Recipe_Maker::equipment_templates()
{
    BluePrint_Book res;

    res.icons.set( 1, Item::Named::virtual_signal("T") );
    res.icons.set( 2, Item::get("exoskeleton-equipment") );
    res.icons.set( 3, Item::get("personal-roboport-mk2-equipment") );
    res.icons.set( 4, Item::get("fusion-reactor-equipment") );

    res.add( A2_assemble_with_recipe(Item::get("low-density-structure"), 1) );

    res.add( A2_assemble_with_recipe(Item::get("exoskeleton-equipment"), 1) );
    res.add( A2_assemble_with_recipe(Item::get("power-armor"), 0) );
    res.add( A2_assemble_with_recipe(Item::get("power-armor-mk2"), 1) );
    res.add( A2_assemble_with_recipe(Item::get("battery-equipment"), 1) );
    res.add( A2_assemble_with_recipe(Item::get("battery-mk2-equipment"), 1) );
    res.add( A2_assemble_with_recipe(Item::get("belt-immunity-equipment"), 0) );
    res.add( A2_assemble_with_recipe(Item::get("night-vision-equipment"), 0) );
    res.add( A2_assemble_with_recipe(Item::get("personal-roboport-equipment"), 1) );
    res.add( A2_assemble_with_recipe(Item::get("personal-roboport-mk2-equipment"), 1) );
    res.add( A2_assemble_with_recipe(Item::get("fusion-reactor-equipment"), 1) );
    res.add( A2_assemble_with_recipe(Item::get("energy-shield-equipment"),  1) );
    res.add( A2_assemble_with_recipe(Item::get("energy-shield-mk2-equipment"), 1) );
    res.add( A2_assemble_with_recipe(Item::get("laser-turret"), 1) );
    res.add( A2_assemble_with_recipe(Item::get("personal-laser-defense-equipment"), 1) );
    return res;
}
//=======================================================================================
#include "raw_equipment.h"
BluePrint_Book Recipe_Maker::equipment()
{
    return BluePrint_Book::do_import( raw_equipment_book );
}
//=======================================================================================
BluePrint_Book Recipe_Maker::sorting()
{
    BluePrint_Book res;
    auto fn = A2_assemble_with_recipe;

    // concrete && stone-brick
    {
        auto centrifuge       = Item::get( "centrifuge" );
        auto nuclear_reactor  = Item::get( "nuclear-reactor" );
        auto oil_refinery     = Item::get( "oil-refinery" );
        auto electric_furnace = Item::get( "electric-furnace" );
        auto artillery_turret = Item::get( "artillery-turret" );
        res.add( fn(centrifuge,       1) );
        res.add( fn(nuclear_reactor,  1) );
        res.add( fn(oil_refinery,     1) );
        res.add( fn(electric_furnace, 1) );
        res.add( fn(artillery_turret, 1) );
    }
    res.next_line();
    {
        auto heat_pipe = Item::get( "heat-pipe" );
        auto heat_exchanger = Item::get( "heat-exchanger" );
        auto steam_turbine = Item::get( "steam-turbine" );
        auto roboport = Item::get( "roboport" );
        res.add( fn(heat_pipe, 1) );
        res.add( fn(heat_exchanger, 1) );
        res.add( fn(steam_turbine, 1) );
        res.add( fn(roboport, 1) );
    }
    res.next_line();
    {
        auto pipe = Item::get( "pipe" );
        auto pump = Item::get( "pump" );
        auto offshore_pump = Item::get( "offshore-pump" );
        auto pipe_to_ground = Item::get( "pipe-to-ground" );
        auto chemical_plant = Item::get( "chemical-plant" );
        auto fluid_wagon = Item::get( "fluid-wagon" );
        auto storage_tank = Item::get( "storage-tank" );
        res.add( fn(pipe, 1) );
        res.add( fn(pipe_to_ground, 1) );
        res.add( fn(pump, 1) );
        res.add( fn(offshore_pump, 1) );
        res.add( fn(chemical_plant, 1) );
        res.add( fn(fluid_wagon, 1) );
        res.add( fn(storage_tank, 1) );
    }
    res.next_line();
    {
        auto landfill = Item::get( "landfill" );
        auto rail = Item::get( "rail" );
        auto train_stop = Item::get( "train-stop" );
        auto iron_stick = Item::get( "iron-stick" );
        res.add( fn(landfill, 1) );
        res.add( fn(iron_stick, 1) );
        res.add( fn(rail, 1) );
        res.add( fn(train_stop, 1) );
    }
    res.next_line();
    {
        auto engine_unit = Item::get( "engine-unit" );
        auto locomotive = Item::get( "locomotive" );
        auto pumpjack = Item::get( "pumpjack" );
        res.add( fn(engine_unit, 1) );
        res.add( fn(locomotive, 1) );
        res.add( fn(pumpjack, 1) );
    }
    res.next_line();
    {
        auto repair_pack = Item::get( "repair-pack" );
        auto electric_mining_drill = Item::get( "electric-mining-drill" );
        auto radar = Item::get( "radar" );
        auto solar_panel = Item::get( "solar-panel" );
        auto cargo_wagon = Item::get( "cargo-wagon" );
        auto rail_signal = Item::get( "rail-signal" );
        auto rail_chain_signal = Item::get( "rail-chain-signal" );
        auto accumulator = Item::get( "accumulator" );
        res.add( fn(repair_pack, 1) );
        res.add( fn(electric_mining_drill, 1) );
        res.add( fn(radar, 1) );
        res.add( fn(solar_panel, 1) );
        res.add( fn(cargo_wagon, 1) );
        res.add( fn(rail_signal, 1) );
        res.add( fn(rail_chain_signal, 1) );
        res.add( fn(accumulator, 1) );
    }

    return res;
}
//=======================================================================================
BluePrint Recipe_Maker::assembling_machines()
{
    return BluePrint::do_import( raw_assembling_machines );
}
//=======================================================================================
#include "raw_manipulators.h"
BluePrint Recipe_Maker::manipulators()
{
    return BluePrint::do_import( raw_manipulators );
}
//=======================================================================================
#include "raw_poles.h"
BluePrint Recipe_Maker::poles()
{
    return BluePrint::do_import( raw_poles );
}
//=======================================================================================
#include "raw_logistics.h"
BluePrint Recipe_Maker::logistics()
{
    return BluePrint::do_import( raw_logistics );
}
//=======================================================================================
#include "raw_drons.h"
BluePrint Recipe_Maker::drons()
{
    return BluePrint::do_import( raw_dron_production_and_loading_to_dronstation );
}
//=======================================================================================
#include "raw_six_advanced_circuits.h"
BluePrint Recipe_Maker::six_advanced_circuits()
{
    auto res = BluePrint::do_import( raw_six_advanced_circuits );
    res.icons.clear();
    res.icons.set( 1, "advanced-circuit" );
    res.icons.set( 2, "signal-6" );

    return res;
}
//=======================================================================================
BluePrint_Book Recipe_Maker::book()
{
    BluePrint_Book res;

    res.icons.set( 1, "signal-A" );
    res.icons.set( 2, "signal-S" );
    res.icons.set( 3, "signal-S" );
    res.icons.set( 4, "signal-M" );

    res.add( drons() );
    res.add( chests() );
    res.next_line();

    res.add( logistics() );
    res.add( assembling_machines() );
    res.add( poles() );
    res.add( manipulators() );
    res.add( L3_belts() );
    res.add( five_labs() );
    //res.next_line();

    res.add( equipment() );
    res.next_line();

    res.add( engine_head() );
    res.add( six_advanced_circuits() );

    return res;
}
//=======================================================================================
