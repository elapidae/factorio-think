#include "landfill_from_clipboard.h"

Landfill_From_Clipboard::Landfill_From_Clipboard()
{

}

/*


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


*/
