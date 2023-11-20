#include "blueprint_book.h"

#include <algorithm>
#include "vlog.h"
#include "blueprint_io.h"
#include "qdeb.h"
#include "names.h"

//=======================================================================================
Blueprint_Book Blueprint_Book::do_import( const QByteArray &arr )
{
    auto obj = BluePrint_IO::extract( arr );
    {
        auto keys = obj.keys();
        if ( keys.size() != 1 || keys.at(0) != "blueprint_book" )
            throw verror;
        obj = obj["blueprint_book"].toObject();
    } // extract book from obj

    auto item  = obj["item"].toString();
    if ( item != "blueprint-book" ) throw verror;

    auto label = obj["label"].toString();
    auto desc  = obj["description"].toString();
    Blueprint_Book res( label, desc );

    res.version = obj["version"].toDouble();
    res.icons.load_raw( obj["icons"].toArray() );

    auto bps = obj["blueprints"].toArray();
    for ( auto bp: bps )
    {
        auto o = bp.toObject();
        auto cur_bp_obj = o["blueprint"].toObject();
        auto idx = o["index"].toDouble();
        auto cur_bp = BluePrint( cur_bp_obj );
        res.blueprints_map.emplace( idx, cur_bp );
    }
    return res;
}
//=======================================================================================
Blueprint_Book::Blueprint_Book( QString label, QString description )
    : label( label )
    , description( description )
{}
//=======================================================================================
QJsonObject Blueprint_Book::build() const
{
    QJsonObject res;
    res["label"] = label;
    res["description"] = description;
    res["active_index"] = active_index;
    res["blueprints"] = blueprints();
    res["icons"] = icons.build();
    res["item"] = "blueprint-book";
    res[names::version] = version;
    return res;
}
//=======================================================================================
QJsonObject Blueprint_Book::build_for_export() const
{
    QJsonObject res;
    res["blueprint_book"] = build();
    return res;
}
//=======================================================================================
void Blueprint_Book::add( const BluePrint& bp )
{
    assign( bp, cur_idx );
}
//=======================================================================================
void Blueprint_Book::assign( const BluePrint& bp, const unsigned idx )
{
    blueprints_map.emplace( idx, bp );
    cur_idx = std::max( cur_idx, idx + 1 );
}
//=======================================================================================
void Blueprint_Book::shift_to( unsigned idx )
{
    if ( idx > 5 ) throw verror;
    while ( cur_idx % 6 != idx )
    {
        ++cur_idx;
    }
}
//=======================================================================================
void Blueprint_Book::next_line()
{
    while ( cur_idx % 6 ) ++cur_idx;
}
//=======================================================================================
void Blueprint_Book::set_burner_inserters_stack_size_1()
{
    for ( auto && bp: blueprints_map )
    {
        bp.second.set_burner_inserters_stack_size_1();
    }
}
//=======================================================================================
QJsonArray Blueprint_Book::blueprints() const
{
    QJsonArray res;
    for ( const auto& [idx, bp]: blueprints_map )
    {
        QJsonObject o;
        o["index"] = double(idx);
        o["blueprint"] = bp.build();
        res.append( o );
    }
    return res;
}
//=======================================================================================

