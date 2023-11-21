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


//=======================================================================================
int main( int argc, char** argv )
{
    //    auto ass_tmpl = PR_Assemble_tmpl::S2_templates();
    auto bp_burn_green  = PR_Burn_Prod_Green_AS_IS::build();
    //    auto rs_pairs = PR_Fluid_CoalStation::rs_pairs();
    auto bp_fluids      = PR_Fluids::build();
    auto bp_science_2   = PR_Science_Before_Rocket::build();
    auto bp_uran        = PR_Uran::build();

    auto bp_zero        = PR_Zero_Book_AS_IS::build();
    auto bp_destructors = PR_Descructors::build();
    auto bp_trains      = PR_Trains_V2::build();
    //clipboard::put( BluePrint_IO::pack(bp_zero.build_for_export()) );
    //clipboard::put( BluePrint_IO::pack(bp_destructors.build_for_export()) );
    clipboard::put( BluePrint_IO::pack(bp_trains.build_for_export()) );

    Blueprint_Book res;

    //res.add( bp_burn_green.build() );



    return 0;


    //auto cp = "chemical-science-pack";
    auto rk = Recipe::keys();
    Blueprint_Book book;
    for ( auto && k: rk )
    {
        BluePrint bp;
        try {
            auto item = Item::get(k);
            bp = Recipe::make_assemble_2( k, -3 );
        }  catch (...) {
            vdeb << "---------- dropped " << k;
            continue;
        }
        vdeb << k;
        book.add( bp );
    }
    auto packed = BluePrint_IO::pack( book.build_for_export() );
    clipboard::put( packed );
    return 0;

    auto bp = BluePrint::do_import( product_iron1() );
    clipboard::put( bp.do_export() );
    return 0;

    make_books(); return 0;

    QApplication app(argc, argv);

    auto clipboard = app.clipboard();

    bool my_change = false;

    auto l = [&]( QClipboard::Mode m )
    {
        if ( m != QClipboard::Clipboard ) return;
        if ( my_change ) return;

        auto text = clipboard->text().toLatin1();
        if ( text.isEmpty() || text.at(0) != '0' ) return;
        vdeb << "changed" << m;
        QJsonObject jo;
        try
        {
            jo = BluePrint_IO::extract( text );
        }
        catch ( const impl_vlog::error& e )
        {
            vdeb << "not extracted";
            return;
        }
        auto r = BPrint_Landfill::correct_blueprint_landfill( jo );
        auto res = BluePrint_IO::pack( r );

        my_change = true;
        app.clipboard()->setText( res );
        my_change = false;
    };

    QObject::connect( clipboard, &QClipboard::changed, l );

    return app.exec();
}
//=======================================================================================
