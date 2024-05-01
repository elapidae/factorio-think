#include <QApplication>
#include <string>
#include "vlog.h"
#include <QFile>
#include <QClipboard>


#include "vcat.h"
#include "bprint_landfill.h"
#include "blueprint_io.h"

#include "make_books.h"
#include "blueprint.h"

#include "recipe.h"
#include "item.h"
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
#include "v2-books/burning_factory_tier1.h"
#include "v2-books/city_blocks.h"
#include "v2-books/assemble/recipe_maker.h"

//=======================================================================================
int main(int c, char **v)
{
    QApplication app(c, v);

    //auto book = Train_Stations::R_solid_intermediate_stops();
    //auto book = Train_Stations::S_solid_intermediate_stops();
    //auto book = Burning_Factory_tier1::tier1();
    //auto book = Train_Stations::RS_fluid_intermediate_stops();
    //auto book = Recipe_Maker::Belt_templates();
    //auto book = Recipe_Maker::Engine_templates();
    //auto book = Recipe_Maker::Chest_templates();
    auto book = Recipe_Maker::Equipment_templates();

    auto res1 = BluePrint_IO::pack( book.build_for_export() );
    clipboard::put( res1 );
    return 0;

    //auto B_rails = City_Blocks::B_rails_one_side_directions();
    //auto M_rails  = City_Blocks::M_rails_between_lines();
    auto rails = City_Blocks::O_rails_for_endpoints();
    clipboard::put( rails.do_export() );
    return 0;

    //PR_War_Assemblies a;
    //return 0;
    //Calc_Lazy_Bastard();
    //return 0;
    //    auto ass_tmpl = PR_Assemble_tmpl::S2_templates();
    //    auto rs_pairs = PR_Fluid_CoalStation::rs_pairs();

    auto bp_zero        = PR_Zero_Book_AS_IS::build();
    auto bp_destructors = PR_Descructors::build();
    auto bp_raw         = PR_Old_Templates_AS_IS::build();

    auto bp_trains      = PR_Trains_V2::build();
    auto bp_burn_green  = PR_Burn_Prod_Green_AS_IS::build();
    auto bp_fluids      = PR_Fluids::build();
    auto bp_science_2   = PR_Science_Before_Rocket::build();
    auto bp_uran        = PR_Uran::build();
    auto bp_war_tmpl    = PR_War_Assemblies::build();

    auto bp_logistics = PR_Logistic_Templates::build();

    auto bp_chests_tmpl = PR_Chests::tmpl();
    auto bp_uran_tmpl = PR_Uran::assemble_tmpl();

    //auto bp_basic_feat2 = PR_Basic_Features_St2::recipies_for_arch();

    BluePrint_Book res;
    res.icons.set( 1, Item::Named::virtual_signal("A") );
    res.icons.set( 2, Item::Named::virtual_signal("L") );
    res.icons.set( 3, Item::Named::virtual_signal("L") );

    res.add( bp_zero );
    res.add( bp_destructors );
    res.add( bp_raw );
    res.next_line();

    res.add( bp_trains );
    res.add( bp_burn_green );
    res.add( bp_fluids );
    res.add( bp_science_2 );
    res.add( bp_uran );

    //auto exp = res.build_for_export();
    //auto pack = BluePrint_IO::pack( exp );
    //clipboard::put( pack );
    //clipboard::put( BluePrint_IO::pack(bp_burn_green.build_for_export()) );
    //clipboard::put( BluePrint_IO::pack(bp_trains.build_for_export()) );
    //clipboard::put( BluePrint_IO::pack(bp_war_tmpl.build_for_export()) );
    //clipboard::put( BluePrint_IO::pack(bp_zero.build_for_export()) );
    //clipboard::put( BluePrint_IO::pack(bp_destructors.build_for_export()) );
    //clipboard::put( BluePrint_IO::pack(bp_trains.build_for_export()) );
    //clipboard::put( BluePrint_IO::pack(bp_fluids.build_for_export()) );
    //clipboard::put( BluePrint_IO::pack(bp_science_2.build_for_export()) );
    //clipboard::put( BluePrint_IO::pack(bp_uran.build_for_export()) );
    //clipboard::put( BluePrint_IO::pack(bp_burn_green.build_for_export()) );
    //clipboard::put( BluePrint_IO::pack(bp_raw.build_for_export()) );
    //clipboard::put( BluePrint_IO::pack(bp_logistics.build_for_export()) );
    //clipboard::put( BluePrint_IO::pack(bp_chests_tmpl.build_for_export()) );
    //clipboard::put( BluePrint_IO::pack(bp_uran_tmpl.build_for_export()) );
    //clipboard::put( BluePrint_IO::pack(bp_basic_feat2.build_for_export()) );


    auto _ = PR_Basic_Features_St2::templates_for_fabric();
    clipboard::put( BluePrint_IO::pack(_.build_for_export()) );
    //BluePrint::test_positions();

    return 0;
}
//=======================================================================================
