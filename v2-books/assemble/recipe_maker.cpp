#include <iostream>
#include "recipe_maker.h"

#include "qdeb.h"
#include "items/constant_combinator.h"
#include "items/assembling_machine.h"
#include "items/chests.h"

//=======================================================================================
static auto assemble_template_medium_pole = R"(0eNqtlN1ugzAMhd/F11C1QP/
Q3mSqqgAutQQJS0w1hHj3JemK2Nq1W7UbpEDs75zjhB6yqsVGk2RIe6BcSQPpaw+GSikq9467BiEFYqwhAClqtxLG
YJ1VJMuwFvmRJIYRDAGQLPAd0sUQ3GhxIs2tfTN2Oe8IC8WT2mjYBYCSiQnPWvyi28u2zlDb5vdVBNAoY4uVdGjXM
IpnywA6WxmvZktL0piTV1RjQW0dYoU5a8rDRlUITvs3ZDQiK1WSYbs1P6Lh0LDSosT70K2H2milxZBPuIeFe5QaUU
49UgFpPBHg1smwG7zot9Yi9weqGPU5mUvco7ybhhy7dQOe207X5uKxmqRBbZvft7O52GGtqn2GR3Eipd3GnHTeEu/
tt2KsPpC2qn99GITs2E6yhDPDsPDK3aJuhBbsUPACw18ijVyEN6wnI/2CCi0mI+kxN1JIrod6lcJ0QA+u0Q/n7zKv
cDG5Ubv/MLx83vDmOcMPLv2n069G3R/AB5VOfk8BnCzEa4s2i2S9jdab1XYez5Nh+ADMAJzH)";
static BluePrint medium_pole_dot_template()
{
    static auto res = BluePrint::do_import( assemble_template_medium_pole );
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
BluePrint_Book Recipe_Maker::Belt_templates()
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
BluePrint Recipe_Maker::L3_Belts()
{
    return BluePrint::do_import( belts_L3_assemble );
}
//=======================================================================================


//=======================================================================================
BluePrint_Book Recipe_Maker::Engine_templates()
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
BluePrint Recipe_Maker::Engine_head()
{
    return BluePrint::do_import( raw_engine_head_bp );
}
//=======================================================================================
BluePrint_Book Recipe_Maker::Chest_templates()
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
#include "raw_chests.h"
BluePrint Recipe_Maker::Chests()
{
    return BluePrint::do_import( raw_chests_bp );
}
//=======================================================================================
BluePrint_Book Recipe_Maker::Equipment_templates()
{
    BluePrint_Book res;

    res.icons.set( 1, Item::Named::virtual_signal("T") );
    res.icons.set( 2, Item::get("exoskeleton-equipment") );
    res.icons.set( 3, Item::get("personal-roboport-mk2-equipment") );
    res.icons.set( 4, Item::get("fusion-reactor-equipment") );

     res.add( A2_assemble_with_recipe(Item::get("exoskeleton-equipment"), 1) );
     res.add( A2_assemble_with_recipe(Item::get("power-armor"), 1) );
     res.add( A2_assemble_with_recipe(Item::get("power-armor-mk2"), 1) );
     res.add( A2_assemble_with_recipe(Item::get("battery-equipment"), 1) );
     res.add( A2_assemble_with_recipe(Item::get("battery-mk2-equipment"), 1) );
     res.add( A2_assemble_with_recipe(Item::get("belt-immunity-equipment"), 1) );
     res.add( A2_assemble_with_recipe(Item::get("night-vision-equipment"), 1) );
     res.add( A2_assemble_with_recipe(Item::get("personal-roboport-equipment"), 1) );
     res.add( A2_assemble_with_recipe(Item::get("personal-roboport-mk2-equipment"), 1) );
     res.add( A2_assemble_with_recipe(Item::get("fusion-reactor-equipment"), 1) );
     res.add( A2_assemble_with_recipe(Item::get("energy-shield-equipment"), 1) );
     res.add( A2_assemble_with_recipe(Item::get("energy-shield-mk2-equipment"), 1) );

     return res;
}
//=======================================================================================
