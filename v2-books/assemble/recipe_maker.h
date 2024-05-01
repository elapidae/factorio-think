#ifndef RECIPE_MAKER_H
#define RECIPE_MAKER_H

#include "blueprint_book.h"
#include "recipe.h"

//=======================================================================================
class Recipe_Maker
{
public:
    static BluePrint A2_assemble_with_recipe( Item item, int count );

    static BluePrint_Book Belt_templates();
    static BluePrint L3_Belts();

    static BluePrint_Book Engine_templates();
    static BluePrint Engine_head();

    static BluePrint_Book Chest_templates();
    static BluePrint Chests();

    static BluePrint_Book Equipment_templates();
};
//=======================================================================================

#endif // RECIPE_MAKER_H
