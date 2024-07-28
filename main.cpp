#include <QApplication>
#include <string>
#include "vlog.h"
#include <QFile>
#include <QClipboard>


#include "vcat.h"
#include "bprint_landfill.h"
#include "blueprint_io.h"

#include "recipe.h"
#include "blueprint_book.h"
#include "clipboard.h"
#include "qdeb.h"
#include "items/inserter.h"
#include "preparations/pr_uran.h"
#include "preparations/pr_trains_v2.h"
#include "clipboard.h"
#include "vtime_meter.h"
#include "preparations/pr_fluids.h"
#include "preparations/pr_fluid_coalstation.h"
#include "preparations/pr_assemble_tmpl.h"
#include "preparations/pr_burn_prod_green_as_is.h"
#include "preparations/pr_zero_book_as_is.h"
#include "preparations/pr_science_before_rocket.h"
#include "preparations/pr_descructors.h"
#include "preparations/pr_old_templates_as_is.h"
#include "preparations/pr_war_assemblies.h"
#include "preparations/pr_logistic_templates.h"
#include "calc_lazy_bastard.h"
#include "preparations/pr_chests.h"
#include "preparations/pr_basic_features_st2.h"

#include "v2-books/train_stations.h"
#include "v2-books/city_blocks.h"
#include "v2-books/assemble/recipe_maker.h"
#include "v2-books/furnaces.h"
#include "v2-books/tier0.h"
#include "v2-books/electricity.h"
#include "v2-books/intermediate_production_l1.h"
#include "v2-books/assemblies_before_drons.h"
#include "v2-books/oil_refinery.h"
#include "v2-books/warehouse.h"

//=======================================================================================
int main(int c, char **v)
{
    QApplication app(c, v);

    BluePrint_Book book;
    //auto book = Recipe_Maker::Belt_templates();
    //auto book = Recipe_Maker::Engine_templates();
    //auto book = Recipe_Maker::Chest_templates();
    //auto book = Recipe_Maker::Equipment_templates();
    //auto book = Recipe_Maker::Equipment();
    //auto book = Recipe_Maker::sorting();
    //auto book = Recipe_Maker::Manipulators();
    //auto book = Recipe_Maker::Poles();
    //auto book = Recipe_Maker::Logistics();
    //auto book = Tier0::prepare_chests();
    //auto book = Electricity::tier1();
    //auto book = Tier0::tier0_book();
    //auto book = Tier0::first_recipies();
    //auto book = Furnances::tier012();
    //auto book = Train_Stations::RS_fluid_intermediate_stops();
//    book = Recipe_Maker::book();
//    book = City_Blocks::book();
//    book = Intermediate_Production_L1::book();
    //book = Train_Stations::S_solid_intermediate_stops();
    book = Furnances::electricFurnances_trainPlant_Tier3();
    //book = Assemblies_Before_Drons::templates();
    //book = Train_Stations::book();
    //book = Oil_Refinery::book();
    book = Warehouse::warehouses();

    auto res = BluePrint_IO::pack( book.build_for_export() );
    clipboard::put( res );
    return 0;
}
//=======================================================================================
