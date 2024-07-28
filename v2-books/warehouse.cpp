#include "warehouse.h"

#include "raw_warehouse.h"
#include "items/chests.h"

static BluePrint do_mine_station( Item item )
{
    static auto tmpl = Item::Named::coal();
    static auto _bp = BluePrint::do_import( raw_mine_train_station_copper );
    auto res = _bp;

    res.icons.clear();
    res.icons.set( 1, "signal-M" );
    res.icons.set( 2, item );

    res.train_stops_replace( tmpl, item );
    res.constant_combinators_replace( tmpl, item );
    auto count = item.stack_size * 8 * 6; // half of wooden chest * 6 chests
    res.decider_combinators_replace_first_signal_count( tmpl, item, count );

    res.schedules.replace( 0, tmpl, item );

    return res;
}

static BluePrint do_warehouse( Item item )
{
    static auto copper = Item::Named::copper_ore();
    static auto _bp = BluePrint::do_import( raw_warehouse_copper );
    auto res = _bp;

    //res.icons.replace_all( coal, item );
    res.icons.set( 1, "signal-W" );
    res.icons.set( 2, "signal-S" );
    res.icons.set( 3, item );
    res.icons.set( 4, item );

    res.train_stops_replace( copper, item );
    res.constant_combinators_replace( copper, item );

    auto count = item.stack_size * 8 * 6; // half of wooden chest * 6 chests
    res.decider_combinators_replace_first_signal_count( copper, item, count );

    res.schedules.replace( 0, copper, item );

    auto schests = res.find( Chests::chest_storage() );
    for ( auto ch: schests )
    {
        Chests::Storage{ch}.filter( item );
    }

    return res;
}

BluePrint_Book Warehouse::warehouses()
{
    BluePrint_Book res;
    auto ware = &do_warehouse;
    auto mine = &do_mine_station;

    auto fn = [&]( Item item )
    {
        res.add( ware(item) );
        res.add( mine(item) );
        res.inc_pos();
    };

    res.icons.clear();
    res.icons.set( 1, "signal-W" );
    res.icons.set( 2, "signal-S" );
    res.icons.set( 3, "signal-M" );

    fn("coal");
    fn("stone");

    fn("copper-ore");
    fn("iron-ore");

    fn("stone-brick");
    fn("copper-plate");

    fn("iron-plate");
    fn("steel-plate");

    return res;
}
