#ifndef RECIPE_MAKER_H
#define RECIPE_MAKER_H

#include "blueprint_book.h"
#include "recipe.h"
#include "../science.h"

//=======================================================================================
class Recipe_Maker
{
public:
    static BluePrint A1_assemble_with_recipe( Item item, int count );
    static BluePrint A1_assemble_without_recipe( int count, QString label );
    static BluePrint A2_assemble_with_recipe( Item item, int count );

    // Scan all entities find assembling machines and fix recipies from them.
    // NB! Count == zeros
    static BluePrint_Book extracted_recipies( QByteArray raw_bp );

    static BluePrint_Book belt_templates();
    static BluePrint_Book engine_templates();
    static BluePrint_Book chest_templates();
    static BluePrint_Book equipment_templates();

    // this is a list of any-many recipies, almost all needed recipies, without groups.
    static BluePrint_Book sorting();

    static BluePrint L3_belts();
    static BluePrint engine_head();
    static BluePrint chests();
    static BluePrint_Book equipment();
    static BluePrint assembling_machines();
    static BluePrint manipulators();
    static BluePrint poles();
    static BluePrint logistics();
    static BluePrint drons();
    static BluePrint five_labs() { return Science::five_science_labs(); }

    static BluePrint six_advanced_circuits();

    static BluePrint_Book book();
};
//=======================================================================================

#endif // RECIPE_MAKER_H
