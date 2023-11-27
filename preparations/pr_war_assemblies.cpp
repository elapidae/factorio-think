#include "pr_war_assemblies.h"

#include <iostream>
#include "recipe.h"
#include "qdeb.h"

static auto tmpl = R"(
0eNqllt1uozAQhd9lrnEV2wQCr1JVK0OmiVX/UNt0i6K8+xqqbZuUQAmXRmY+n5kzY5+gUi02TpoA5QlkbY2H8vEEXh6MUP230DUIJciAGhIwQvcr4T3qSklzIFrUR2mQMDgnIM0e36Gk56cE0AQZJH7EGxbdH9PqCl3cMB0pgcb6+LM1/QliQFbkD9sEOigJLR62keSwlsPB0KA7dMQfJao9wddWNjrS4ml+UNlCKt9sfkfVL2yazD/JGvey1QQV1sHJmjRW4RiZ/SezzUA2KA/HyrauzydlTyOQdLG89Ja8SoSArpsWtV3My+d4s4nMVhgnu2Q26LyNJifOVraxLkyT8xXmmSXP6t6tqO013f5FR4TT1o2RihVV7UkjIelmRdX45elNbINA3qSPu6dTRumKil1RK1SBSK1bEwkzWLa41/knNv3Z6zyh+Vi3U77CEuxSnrdKONIIg2pGXLrCHVfQ53aooUNRB+tmuNv7HXQ9ud+tf4klCbP+ye73T3Gj4ZXwsff2+IzG4ww+v//OoPS3dwZdPlj4DZEf2kLrHI4LWj5Zslv5/Bph/eiE/rkxPFDKb++ZBN5i2odwbEfTvGB5vuM7zrPz+R9lXvUH
)";

PR_War_Assemblies::PR_War_Assemblies()
{
    auto tmp = BluePrint::do_import(tmpl);
    auto list = Recipe::extract_recipies( tmp );
    for (auto&& l:list)
    {
        auto name = l.name;
        auto label = name;
        label.replace("-", "_");
        std::cout << "    auto " << label << " = Item::get( \"" << name << "\" );\n";
        std::cout << "    " << label << ".prefer_assemble_count( 1 );" << std::endl;
        std::cout << "    bp = Recipe::form_in_assembling_machine_2( " << label << " );" << std::endl;
        std::cout << "    res.add( bp );\n" << std::endl;
    }
}

Blueprint_Book PR_War_Assemblies::build()
{
    Blueprint_Book res;
    res.icons.set( 1, Item::Named::virtual_signal("W") );
    res.icons.set( 2, Item::Named::virtual_signal("A") );
    res.icons.set( 3, Item::Named::virtual_signal("R") );
    res.icons.set( 4, Item::Named::virtual_signal("T") );
    BluePrint bp;

    auto energy_shield_equipment = Item::get( "energy-shield-equipment" );
    energy_shield_equipment.prefer_assemble_count( 1 );
    bp = Recipe::form_in_assembling_machine_2( energy_shield_equipment );
    res.add( bp );

    auto energy_shield_mk2_equipment = Item::get( "energy-shield-mk2-equipment" );
    energy_shield_mk2_equipment.prefer_assemble_count( 1 );
    bp = Recipe::form_in_assembling_machine_2( energy_shield_mk2_equipment );
    res.add( bp );

    auto battery_equipment = Item::get( "battery-equipment" );
    battery_equipment.prefer_assemble_count( 1 );
    bp = Recipe::form_in_assembling_machine_2( battery_equipment );
    res.add( bp );

    auto battery_mk2_equipment = Item::get( "battery-mk2-equipment" );
    battery_mk2_equipment.prefer_assemble_count( 1 );
    bp = Recipe::form_in_assembling_machine_2( battery_mk2_equipment );
    res.add( bp );

    auto personal_roboport_equipment = Item::get( "personal-roboport-equipment" );
    personal_roboport_equipment.prefer_assemble_count( 1 );
    bp = Recipe::form_in_assembling_machine_2( personal_roboport_equipment );
    res.add( bp );

    auto personal_roboport_mk2_equipment = Item::get( "personal-roboport-mk2-equipment" );
    personal_roboport_mk2_equipment.prefer_assemble_count( 1 );
    bp = Recipe::form_in_assembling_machine_2( personal_roboport_mk2_equipment );
    res.add( bp );

    auto power_armor = Item::get( "power-armor" );
    power_armor.prefer_assemble_count( 1 );
    bp = Recipe::form_in_assembling_machine_2( power_armor );
    res.add( bp );

    auto night_vision_equipment = Item::get( "night-vision-equipment" );
    night_vision_equipment.prefer_assemble_count( 1 );
    bp = Recipe::form_in_assembling_machine_2( night_vision_equipment );
    res.add( bp );

    auto belt_immunity_equipment = Item::get( "belt-immunity-equipment" );
    belt_immunity_equipment.prefer_assemble_count( 1 );
    bp = Recipe::form_in_assembling_machine_2( belt_immunity_equipment );
    res.add( bp );

    auto solar_panel_equipment = Item::get( "solar-panel-equipment" );
    solar_panel_equipment.prefer_assemble_count( 1 );
    bp = Recipe::form_in_assembling_machine_2( solar_panel_equipment );
    res.add( bp );

    auto fusion_reactor_equipment = Item::get( "fusion-reactor-equipment" );
    fusion_reactor_equipment.prefer_assemble_count( 1 );
    bp = Recipe::form_in_assembling_machine_2( fusion_reactor_equipment );
    res.add( bp );

    auto exoskeleton_equipment = Item::get( "exoskeleton-equipment" );
    exoskeleton_equipment.prefer_assemble_count( 1 );
    bp = Recipe::form_in_assembling_machine_2( exoskeleton_equipment );
    res.add( bp );

    auto personal_laser_defense_equipment = Item::get( "personal-laser-defense-equipment" );
    personal_laser_defense_equipment.prefer_assemble_count( 1 );
    bp = Recipe::form_in_assembling_machine_2( personal_laser_defense_equipment );
    res.add( bp );

    auto laser_turret = Item::get( "laser-turret" );
    laser_turret.prefer_assemble_count( 1 );
    bp = Recipe::form_in_assembling_machine_2( laser_turret );
    res.add( bp );

    auto power_armor_mk2 = Item::get( "power-armor-mk2" );
    power_armor_mk2.prefer_assemble_count( 1 );
    bp = Recipe::form_in_assembling_machine_2( power_armor_mk2 );
    res.add( bp );

    return res;
}
