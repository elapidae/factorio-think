#include "blueprint.h"

#include "vlog.h"
#include "blueprint_io.h"
#include "items/inserter.h"
#include "items/constant_combinator.h"
#include "items/decider_combinator.h"
#include "items/arithmetic_combinator.h"
#include "qdeb.h"
#include "names.h"

//=======================================================================================
BluePrint BluePrint::do_import( QByteArray raw0 )
{
    auto bp = BluePrint_IO::extract( raw0 );
    //qdeb << bp;
    //exit(1);
    return BluePrint( bp[names::blueprint].toObject() );
}
//=======================================================================================
QByteArray BluePrint::do_export() const
{
    QJsonObject res;
    res[names::blueprint] = build();
    return BluePrint_IO::pack( res );
}
//=======================================================================================


//=======================================================================================
BluePrint::BluePrint( QJsonObject bp )
{
    //-----------------------------------------------------------------------------------
    if ( bp.take(names::item).toString() != names::blueprint )
        throw verror << "item != blueprint";

    version = bp.take(names::version).toDouble();
    if ( version <= 0 ) throw verror << version;

    description     = bp.take(names::description).toString();
    label           = bp.take(names::label).toString();
    //-----------------------------------------------------------------------------------
    entities        = bp.take(names::entities).toArray();
    icons.load_raw  ( bp.take(names::icons).toArray() );
    schedules.arr   = bp.take(names::schedules).toArray();
    tiles           = bp.take(names::tiles).toArray();
    //-----------------------------------------------------------------------------------
    absolute_snapping           = bp.take(names::absolute_snapping).toBool();
    position_relative_to_grid   = bp.take(names::position_relative_to_grid).toObject();
    snap_to_grid                = bp.take(names::snap_to_grid).toObject();
    //-----------------------------------------------------------------------------------
    if ( !bp.isEmpty() ) {
        throw verror << bp.keys();
    }
}
//=======================================================================================
QJsonObject BluePrint::build() const
{
    QJsonObject res;
    //-----------------------------------------------------------------------------------
    res[names::item]        = names::blueprint;
    res[names::version]     = double( version );
    res[names::description] = description;
    res[names::label]       = label;
    //-----------------------------------------------------------------------------------
    res[names::entities]  = entities;
    res[names::icons]     = icons.build();
    res[names::schedules] = schedules.arr;
    res[names::tiles]     = tiles;
    //-----------------------------------------------------------------------------------
    if ( absolute_snapping )
        res[names::absolute_snapping] = absolute_snapping;

    if ( !position_relative_to_grid.isEmpty() )
        res[names::position_relative_to_grid] = position_relative_to_grid;

    if ( !snap_to_grid.isEmpty() )
        res[names::snap_to_grid] = snap_to_grid;
    //-----------------------------------------------------------------------------------
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
void BluePrint::arithmetic_combinators_replace_in_out(Item src, Item dst)
{
    auto list = find( Item::get(names::arithmetic_combinator) );
    for ( auto ref: list )
    {
        Arithmetic_Combinator2 ac( ref );
        ac.replace_in_out( src, dst );
    }
}
//=======================================================================================
void BluePrint::constant_combinators_replace( Item src, Item dst )
{
    auto list = find( Item::get(names::constant_combinator) );
    for ( auto ref: list )
    {
        Constant_Combinator2( ref )
                .replace( src, dst );
    }
}
//=======================================================================================
void BluePrint::decider_combinators_replace_first_signal
                                ( const Item& src, const Item& dst )
{
    auto list = find( Item::get(names::decider_combinator) );
    for ( auto ref: list )
    {
        Decider_Combinator2 dc( ref );
        dc.replace_first_signal( src, dst );
    }
}
//=======================================================================================
void BluePrint::locomotives_init_fuel_coal( int count )
{
    auto list = find( Item::Named::locomotive() );
    for ( auto ref: list )
    {
        auto l = Locomotive{ ref.toObject() };
        l.clear_fuel();
        l.coal( count );
        ref = l.obj;
    }
}
//=======================================================================================
void BluePrint::locomotives_init_fuel_nuclear( int count )
{
    auto list = find( Item::Named::locomotive() );
    for ( auto ref: list )
    {
        auto l = Locomotive{ ref.toObject() };
        l.clear_fuel();
        l.nuclear_fuel( count );
        ref = l.obj;
    }
}
//=======================================================================================
void BluePrint::train_stops_replace( Item src, Item dst )
{
    auto list = find( Item::Named::train_stop() );
    for ( auto ref: list )
    {
        auto ts = Train_Stop{ ref.toObject() };
        ts.replace( src, dst );
        ref = ts.obj;
    }
}
//=======================================================================================
void BluePrint::remove_field( Item item, QString field )
{
    auto list = find( item );
    for ( auto ref: list )
    {
        auto obj = ref.toObject();
        obj.remove( field );
        ref = obj;
    }
}
//=======================================================================================
