#include "blueprint.h"

#include "vlog.h"
#include "blueprint_io.h"
#include "items/inserter.h"
#include "qdeb.h"


//=======================================================================================
BluePrint BluePrint::do_import( QByteArray raw0 )
{
    auto bp = BluePrint_IO::extract( raw0 );
    //qdeb << bp;
    //exit(1);
    return BluePrint( bp[n_blueprint].toObject() );
}
//=======================================================================================
QByteArray BluePrint::do_export() const
{
    QJsonObject res;
    res[n_blueprint] = build();
    return BluePrint_IO::pack( res );
}
//=======================================================================================


//=======================================================================================
BluePrint::BluePrint( QJsonObject bp )
{
    if ( bp.take(n_item).toString() != n_blueprint ) throw verror << "item != blueprint";

    version = bp.take(n_version).toDouble();
    if ( version <= 0 ) throw verror << version;

    entities = bp.take(n_entities).toArray();

    icons.load_raw( bp[n_icons].toArray() );
    bp.remove( n_icons );

    schedules = bp[n_schedules].toArray();
    bp.remove( n_schedules );

    tiles = bp[n_tiles].toArray();
    bp.remove( n_tiles );

    if ( !bp.isEmpty() ) {
        throw verror << bp.keys();
    }
}
//=======================================================================================
QJsonObject BluePrint::build() const
{
    QJsonObject res;

    res[n_item]      = n_blueprint;
    res[n_version]   = double( version );

    res[n_entities]  = entities;
    res[n_icons]     = icons.build();
    res[n_schedules] = schedules;

    res[n_tiles]     = tiles;

    return res;
}
//=======================================================================================
QList<QJsonValueRef> BluePrint::find( Item item )
{
    QList<QJsonValueRef> res;
    for ( int i = 0; i < entities.size(); ++i )
    {
        auto o = entities[i].toObject();
        auto name = o["name"].toString();
        if ( name == item.name )
            res.push_back( entities[i] );
    }
    return res;
}
//=======================================================================================
QJsonValueRef BluePrint::find_unique( Item item )
{
    auto list = find( item );
    if ( list.size() != 1 ) throw verror;
    return list.at( 0 );
}
//=======================================================================================
template <class> class TD;
void BluePrint::set_burner_inserters_stack_size_1()
{
    for ( auto&& e: entities )
    {
        //TD<decltype(e)> td;
        auto o = e.toObject();
        if ( o["name"] != Inserter::burner_inserter ) continue;
        Inserter inserter( o );
        inserter.set_override_stack_size( 1 );
        e = inserter.obj;
    }
}
//=======================================================================================
