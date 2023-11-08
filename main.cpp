#include <QApplication>
#include <string>
#include "vlog.h"
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QClipboard>

#include "parse_lua_recipe.h"
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

const char * product_iron1();

//=======================================================================================
int main( int argc, char** argv )
{
    vtime_meter tm;
    auto trains = PR_Trains_V2::build();
    vdeb << "trains:" << tm.restart().ms();
    auto pack = BluePrint_IO::pack( trains.build_for_export() );
    clipboard::put( pack );
    vdeb << "pack:" << tm.elapsed().ms();
    return 0;

    QMap<QString, int> types;
    auto kk = Item::keys();
    for (auto k: kk) {
        auto it = Item::get(k);
        ++types[it.item_type];
        if (it.item_type == "copy-paste-tool") {
            qdeb << it.item_type << it.name << it.type;
        }
    }
    for (auto kv = types.cbegin(); kv != types.cend(); ++kv) {
        qdeb << kv.key() << kv.value();
    }
    //qdeb << types;
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
