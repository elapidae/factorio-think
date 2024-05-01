#include "blueprint_book.h"

#include <algorithm>
#include "vlog.h"
#include "blueprint_io.h"
#include "qdeb.h"
#include "names.h"

//=======================================================================================
BluePrint_Book BluePrint_Book::do_import( const QByteArray &arr )
{
    auto obj = BluePrint_IO::extract( arr );
    {
        auto keys = obj.keys();
        if ( keys.size() != 1 || keys.at(0) != names::blueprint_book_build )
            throw verror;
        obj = obj[names::blueprint_book_build].toObject();
    } // extract book from obj

    return from_object( obj );
}
//=======================================================================================
BluePrint_Book BluePrint_Book::from_object( QJsonObject obj )
{
    auto item  = obj.take("item").toString();
    if ( item != names::blueprint_book_build && item != names::blueprint_book_label )
        throw verror;

    auto label = obj.take("label").toString();
    auto desc  = obj.take("description").toString();

    BluePrint_Book res( label, desc );
    res.version = obj.take("version").toDouble();
    res.icons.load_raw( obj.take("icons").toArray() );
    res.active_index = obj.take("active_index").toDouble();

    auto bps = obj.take("blueprints").toArray();
    for ( auto bp: bps )
    {
        auto o = bp.toObject();
        auto idx = o.take("index").toDouble();
        auto key = [&o] {
            auto keys = o.keys();
            if ( keys.size() != 1 ) throw verror << "Strange planner " << keys;
            return keys.at(0);
        }();
        if ( key == names::blueprint )
        {
            auto cur_bp = BluePrint( o.take(names::blueprint).toObject() );
            res.blueprints_map.emplace( idx, cur_bp );
            continue;
        }
        if ( key == names::deconstruction_planner )
        {
            Deconstruction_Planner cur_dp;
            cur_dp.obj = o.take(names::deconstruction_planner).toObject();
            res.deconstructions_map.emplace( idx, cur_dp );
            continue;
        }
        if ( key == names::blueprint_book_build ||
             key == names::blueprint_book_label )
        {
            auto book = BluePrint_Book::from_object( o.value(key).toObject() );
            res.books_map.emplace( idx, book );
            continue;
        }
        throw verror << key;
    }
    if ( !obj.isEmpty() ) throw verror;
    return res;
}
//=======================================================================================
BluePrint_Book::BluePrint_Book( QString label, QString description )
    : label( label )
    , description( description )
{}
//=======================================================================================
QJsonObject BluePrint_Book::build() const
{
    QJsonObject res;
    res["label"] = label;
    res["description"] = description;
    res["active_index"] = active_index;
    res["blueprints"] = blueprints();
    res["icons"] = icons.build();
    res["item"] = names::blueprint_book_label;
    res[names::version] = version;
    return res;
}
//=======================================================================================
QJsonObject BluePrint_Book::build_for_export() const
{
    QJsonObject res;
    res["blueprint_book"] = build();
    return res;
}
//=======================================================================================
void BluePrint_Book::add( const BluePrint& bp )
{
    assign( bp, cur_idx );
}
//=======================================================================================
void BluePrint_Book::add( const BluePrint_Book& bp )
{
    assign( bp, cur_idx );
}
//=======================================================================================
void BluePrint_Book::assign( const BluePrint& bp, const unsigned idx )
{
    blueprints_map.emplace( idx, bp );
    cur_idx = std::max( cur_idx, idx + 1 );
}
//=======================================================================================
void BluePrint_Book::assign( const BluePrint_Book& bp, unsigned idx )
{
    books_map.emplace( idx, bp );
    cur_idx = std::max( cur_idx, idx + 1 );
}
//=======================================================================================
void BluePrint_Book::shift_to( unsigned idx )
{
    if ( idx > 5 ) throw verror;
    while ( cur_idx % 6 != idx )
    {
        ++cur_idx;
    }
}
//=======================================================================================
void BluePrint_Book::next_line()
{
    if ( cur_idx % 6 == 0 ) ++cur_idx;
    while ( cur_idx % 6 ) ++cur_idx;
}
//=======================================================================================
void BluePrint_Book::set_burner_inserters_stack_size_1()
{
    for ( auto && bp: blueprints_map )
    {
        bp.second.set_burner_inserters_stack_size_1();
    }
}
//=======================================================================================
QJsonArray BluePrint_Book::blueprints() const
{
    QJsonArray res;
    for ( const auto& [idx, bp]: blueprints_map )
    {
        QJsonObject o;
        o["index"] = double(idx);
        o["blueprint"] = bp.build();
        res.append( o );
    }
    for ( const auto& [idx, dp]: deconstructions_map )
    {
        QJsonObject o;
        o["index"] = double(idx);
        o[names::deconstruction_planner] = dp.obj;
        res.append( o );
    }
    for ( const auto& [idx, book]: books_map )
    {
        QJsonObject o;
        o["index"] = double(idx);
        o[names::blueprint_book_build] = book.build();
        res.append( o );
    }
    return res;
}
//=======================================================================================

