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

//=======================================================================================
int main( int argc, char** argv )
{
    vdeb << __cplusplus;
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
auto blueprint_n = "blueprint";
auto icons = "icons";
auto version = "version";
auto item = "item";
auto entities_n = "entities";
auto tiles_n = "tiles";

