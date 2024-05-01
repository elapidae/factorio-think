#include "blueprint.h"

#include "vlog.h"
#include "blueprint_io.h"
#include "items/inserter.h"
#include "items/constant_combinator.h"
#include "items/decider_combinator.h"
#include "items/arithmetic_combinator.h"
#include "qdeb.h"
#include "names.h"
#include "bprint_landfill.h"


//=======================================================================================
auto test_pos = R"(
0eNqdnO1O40gQRd/Fv5OR+7PavMM8wQqtAlispZBExmEXjXj3tQkK0WyX6979MRoxS47t9mmX69bCr+Zhf+5P43CYmrtfzethd9pOx+3zODwtX//T3MWyad6Xvz42ze7h9bg/T/12+b7TcHhu7qbx3G+a0/F1mIbjYTv2+900vPW/QdpPRvAzY3g8Hl6buz/mgw3Ph91++Y7p/dQ3d80w9S/NpjnsXpav9rvXftxO53Hsp2b54OGpn1HuY1P56NswTuf5X66fvnzH9ufNJ/3H/abpD9N8pv3lDD6/eP/zcH556McZff30827qm+/L+roK536kzwvZxh9p5j4NY/94+e9+OavfcN7CtRQufF/bdDz02793+30FGm6hFUzEMN7AJAyTDEzGMNHACIbJBqZgGDEwHYYpBsa1GKezOA7ieGdxPMZpLQ5msrdMdpjK3lLZYS57S0KHyeytPeEwm71ls8N09pbODvPZWz57zGdv+ewxn4Plocd8Dta+8JjPwfLZYz4Hy2eP+RwsDz3mc7D2hRejEIbM1dVi8YTjYX4Hy++A+R0svwPmd7S8DJjf0donAfM7Wl4GzO9o7ZOA+R0tvwPmd7T8DtjzOlrP2YA9r6P13A+Yz9HyMGI+R2tfRMznZPkcMZ+T5XPEfE7mmzTmc7L2RcR8TpaHEfM5WfsiYj4ny+eI+Zwsn2NnPO9ToZ73qbV4HcfD/M6WlwnzO1v7JGF+Z7PFw/zO1j5JmN/Z8jthfmfL74T5nS0vE+Z3tvZJwp7X2XrOZux5na3nfsZ8FsvDjPks1r7ImM9i+Zwxn8XyOWM+i5l9YD6LtS8y5rNYPmfMZ7F8zpjPYnkomM9i7QvBfC6Wh4L5XKx9IZjPxfJZMJ+L5bMkox6WRNVDyRYvcjyBc9kA8QoczGK8jkxmg5I+tmQ0q3Ecmc1qHE+GsxonkOmsxolkPKtxEpmrapxM5rwaR8h8VuMUMp/VOB2ZzyqcriXzWY3jyHxW43gyn9U4gcxnNU4k81mNk8h8VuNkMp/VOELmqhqnkDmvxunIfDZo85iWDGhVkCMTWhXkyYhWBQU4o4VqomsjHNKCwESmtOqlZjKmVUFC5qsqqJCBrwrqyKRWA4Gjx2huGXD2mGyQJ8M2FRTItE0FRTJuU0GJzNtUUCYDNxUkcOKGbV5X4MgNBHZkVqZdKjiUzOYmBqeS2TQdHEtm03RwLplNQcHBZDa3DDiZzKbp4Ggym6Z7ITMzFVTIEE8FdWRqpoHAcaSYWwScR4opJDiQFHOLgBNJMc0GR5Jimg3OJMU0GxxKimk2OJUU02xwLCmm2eBcsphCgoPJYm4RcDJZTLPB0WQxzY4BzuKwQhkjHMaBwFT/PzQredcF6+oXmlFMWsUIiimrmAJifLuK6VDM6tncDCjXMWH1bG7mkgZm9U7djCUNzOqduplKGphuFRNBzLK3VzCoxXF9bVCL0zoGtTitLzFq8XK8FQxqcV5d4oxanFfXJqMWL+O0FQxqcV7dmhm1WNbPBrVY1s8Gtbis3ynU4rJ+p4SrDAqlcIVBoXRcXahTpOXKgkJxXFVQKJ4rCgolcDVBoUSuJCiUxFUEhZK5gqBQhKsHCqVw5UChdFw1qFNKyxUDheK4WqBQPFcKFErgKoFCiVwhUCiJqwMKJXNlQKEIVwUUSuGKgELpuBoQ6z9w0HI1QKE4rgYolG93X/qn4fyy7fdzgzQOj9vTcd+vzLH9Zz916Ifnvx6O53H5kTMfuvvqQQJXaJRTjVyhUSiJKzQKJZPLdh0H1patbTfq0glX0ZTTLVxFUygdV9Fi/cdkWnLprhOmytItN8LH9r56IMeVTuV0PVc6FUrgSqdCiVzpVCiJvAHXGU/V3U6/AZmr0crpClejFUrharRC6ciluw4NqkuX5qVz1aVzLfcyUD9d57iXAYXiuZcBhRK4lwGFEskbcA2AazdAW3yy71ROlWw7FQrZdeY6hew6FQrZddYpnuw6FQrZdSoUsutUKGTXqVDIrlOhkF2nQiG7ToVCdp0Khew6FQrZddYpgew6FQrZdSoUsutUKGTXqVDIrlOhkF2nQiG7ToVCdp0Khew6Fcq3uw/Ds1XxlufIjJL/vir7zdfr8vzHVyvfzegRONLX706Raj+zvNyETn3BuZlNAkda0sH6keYjzO8El2sK9SP5/7F6IYC9rb8ZaeIXUsEv63S/ufySmLubX1uzad768fUysCwuSuelzE+QlPzHx78p1MZQ
)";
void BluePrint::test_positions()
{
    auto bp = do_import(test_pos);
    qdeb << bp.entities;
}
//=======================================================================================


//=======================================================================================
BluePrint BluePrint::do_import( QByteArray raw0 )
{
    auto bp = BluePrint_IO::extract( raw0 );
    bp = BPrint_Landfill::correct_blueprint_landfill( bp );
    return BluePrint( bp );
}
//=======================================================================================
QByteArray BluePrint::do_export() const
{
    QJsonObject res;
    res[names::blueprint] = build();
    return BluePrint_IO::pack( res );
}
//=======================================================================================
QByteArray BluePrint::do_export_landfill() const
{
    QJsonObject res;
    res[names::blueprint] = build();
    res = BPrint_Landfill::correct_landfill( res );
    return BluePrint_IO::pack( res );
}
//=======================================================================================


//=======================================================================================
BluePrint::BluePrint( QJsonObject bp )
{
    //-----------------------------------------------------------------------------------
    auto keys = bp.keys();
    if ( keys.size() == 1 && keys.at(0) == names::blueprint )
    {
        bp = bp[names::blueprint].toObject();
    }
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
    //-----------------------------------------------------------------------------------
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
QList<QJsonValueRef> BluePrint::find_assembling_machines()
{
    return find( Item::Named::assembling_machine_1() ) +
           find( Item::Named::assembling_machine_2() ) +
           find( Item::Named::assembling_machine_3() );
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
void BluePrint::decider_combinators_replace_first_signal_count
                    ( const Item& src, const Item& dst, int count )
{
    auto list = find( Item::get(names::decider_combinator) );
    for ( auto ref: list )
    {
        Decider_Combinator2 dc( ref );
        dc.replace_first_signal_count( src, dst, count );
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
