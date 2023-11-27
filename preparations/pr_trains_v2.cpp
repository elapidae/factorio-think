#include "pr_trains_v2.h"

#include "vlog.h"
#include "qdeb.h"
#include "items/arithmetic_combinator.h"
#include "items/constant_combinator.h"
#include "items/decider_combinator.h"
#include "items/trains.h"

//=======================================================================================
/*static auto items()
{
    static const auto res = {
        Item::get( "coal"         ),
        Item::get( "iron-ore"     ),
        Item::get( "iron-plate"   ),
        Item::get( "steel-plate"  ),
        Item::get( "copper-ore"   ),
        Item::get( "copper-plate" ),
    };
    return res;
};*/
//=======================================================================================
static BluePrint rv2_6_wood_chests( Item item );
static BluePrint rv2_12_wood_chests( Item item );
template <class> class TD;
Blueprint_Book PR_Trains_V2::build()
{
    Blueprint_Book res;    
    res.icons.set( 1, Item::Named::train_stop() );
    res.icons.set( 2, Item::Named::virtual_signal("R") );
    res.icons.set( 3, Item::Named::virtual_signal("S") );
    res.icons.set( 4, Item::Named::virtual_signal("1") );

    // - send for mining.
    auto gen_fn = send_mine_12;
    res.add( gen_fn(Item::Named::coal())        );
    res.add( gen_fn(Item::Named::stone())       );
    res.add( gen_fn(Item::Named::iron_ore())    );
    res.add( gen_fn(Item::Named::copper_ore())  );
    res.next_line();

    // send for product lines
    gen_fn = send_mine_6;
    res.add( gen_fn(Item::Named::uranium_ore())         );
    res.add( gen_fn(Item::Named::iron_plate())          );
    res.add( gen_fn(Item::Named::steel_plate())         );
    res.add( gen_fn(Item::Named::copper_plate())        );
    res.add( gen_fn(Item::Named::plastic_bar())         );
    res.add( gen_fn(Item::Named::sulfur())              );
    res.add( gen_fn(Item::Named::battery())             );
    res.add( gen_fn(Item::Named::explosives())          );
    res.add( gen_fn(Item::Named::electronic_circuit())  );
    res.next_line();

    // - receive 1L
    gen_fn = rv2_6_wood_chests;
    res.add( gen_fn(Item::Named::coal())                );
    res.add( gen_fn(Item::Named::stone())               );
    res.add( gen_fn(Item::Named::iron_ore())            );
    res.add( gen_fn(Item::Named::copper_ore())          );
    res.add( gen_fn(Item::Named::iron_plate())          );
    res.add( gen_fn(Item::Named::steel_plate())         );
    res.add( gen_fn(Item::Named::copper_plate())        );
    res.add( gen_fn(Item::Named::plastic_bar())         );
    res.add( gen_fn(Item::Named::sulfur())              );
    res.add( gen_fn(Item::Named::battery())             );
    res.add( gen_fn(Item::Named::explosives())          );
    res.add( gen_fn(Item::Named::electronic_circuit())  );
    res.next_line();

    // - receive 2L
    gen_fn = rv2_12_wood_chests;
    res.add( gen_fn(Item::Named::coal())                );
    res.add( gen_fn(Item::Named::stone())               );
    res.add( gen_fn(Item::Named::iron_ore())            );
    res.add( gen_fn(Item::Named::copper_ore())          );
    res.add( gen_fn(Item::Named::iron_plate())          );
    res.add( gen_fn(Item::Named::steel_plate())         );
    res.add( gen_fn(Item::Named::copper_plate())        );
    res.add( gen_fn(Item::Named::plastic_bar())         );
    res.add( gen_fn(Item::Named::sulfur())              );
    res.add( gen_fn(Item::Named::battery())             );
    res.add( gen_fn(Item::Named::explosives())          );
    res.add( gen_fn(Item::Named::electronic_circuit())  );
    res.next_line();

    return res;
}
//=======================================================================================
BluePrint PR_Trains_V2::receive_1L_6_wooden_chests( Item item )
{
    return rv2_6_wood_chests( item );
}
//=======================================================================================
BluePrint PR_Trains_V2::send_mine_6( Item item )
{
    static auto loaded = BluePrint::do_import( send_mine_6_iron_template() );
    auto src = Item::get( "iron-ore" );

    auto res = loaded;
    res.icons.set( 1, Item::Named::train_stop() );
    res.icons.set( 2, item );
    res.icons.set( 3, Item::Named::virtual_signal("S") );
    res.icons.set( 4, Item::Named::virtual_signal("6") );

    // - find & correct decider combinator [visual control yellow/blue];
    auto rdc = res.find_unique( Item::get(names::decider_combinator) );
    auto dc = Decider_Combinator{ rdc.toObject() };
    dc.first_signal( item );
    auto min_count = item.stack_size * 40; // 40 -- wagoon size.
    dc.constant( min_count );
    rdc = dc.obj;

    // - correct arithmetic combinator [filling chests]
    res.arithmetic_combinators_replace_in_out( src, item );

    // - find & correct constant combinators [visual control];
    res.constant_combinators_replace( src, item );

    // - train stop name correction;
    auto rtrain = res.find_unique( Item::Named::train_stop() );
    auto ts = Train_Stop{ rtrain.toObject() };
    ts.set_name( item, "send" );
    rtrain = ts.obj;

    // - correct schedulers
    res.schedules.replace( 0, src, item );

    // - correct locomotive fuel
    auto locs = res.find( Item::Named::locomotive() );
    for ( auto ref: locs )
    {
        auto l = Locomotive{ ref.toObject() };
        l.clear_fuel();
        l.coal( 4 );
        ref = l.obj;
    }

    return res;
}
//=======================================================================================
BluePrint PR_Trains_V2::send_mine_12( Item item )
{
    static auto loaded = BluePrint::do_import( send_mine_12_iron_template() );
    auto src = Item::get( "iron-ore" );

    auto res = loaded;
    res.icons.set( 1, Item::Named::train_stop() );
    res.icons.set( 2, item );
    res.icons.set( 3, Item::Named::virtual_signal("S") );
    res.icons.set( 4, Item::Named::virtual_signal("M") );

    // - correct arithmetic combinator [filling chests]
    res.arithmetic_combinators_replace_in_out( src, item );

    // - find & correct decider combinator [visual control yellow/blue];
    auto rdc = res.find_unique( Item::get(names::decider_combinator) );
    auto dc = Decider_Combinator{ rdc.toObject() };
    dc.first_signal( item );
    auto min_count = item.stack_size * 40; // 40 -- wagoon size.
    dc.constant( min_count );
    rdc = dc.obj;

    // - find & correct constant combinators [visual control];
    res.constant_combinators_replace( src, item );

    // - train stop name correction;
    auto rtrain = res.find_unique( Item::Named::train_stop() );
    auto ts = Train_Stop{ rtrain.toObject() };
    ts.set_name( item, "send" );
    rtrain = ts.obj;

    // - correct schedulers
    res.schedules.replace( 0, src, item );

    // - correct locomotive fuel
    auto locs = res.find( Item::Named::locomotive() );
    for ( auto ref: locs )
    {
        auto l = Locomotive{ ref.toObject() };
        l.clear_fuel();
        l.coal( 4 );
        ref = l.obj;
    }

    return res;
}
//=======================================================================================
static QByteArray rv2_6_wood_chests_coal_template();
// - set override size of burner inserters to 1;
// - find & correct arithmetic combinator [inserters to belt];
// - find & correct decider combinator [train limit];
// - find & correct constant combinators [visual control];
// - train stop name correction;
static BluePrint rv2_6_wood_chests( Item item )
{
    static auto loaded = BluePrint::do_import( rv2_6_wood_chests_coal_template() );
    auto coal = Item::get( "coal" );

    auto res = loaded;
    res.icons.set( 1, item );
    res.icons.set( 2, Item::Named::virtual_signal("R") );
    res.icons.set( 3, Item::Named::virtual_signal("1") );
    res.icons.set( 4, Item::Named::virtual_signal("L") );

    // - set override size of burner inserters to 1;
    res.set_burner_inserters_stack_size_1();

    // - find & correct arithmetic combinator [inserters to belt];
    auto rac = res.find_unique( Item::get(names::arithmetic_combinator) );
    auto ac = Arithmetic_Combinator{ rac.toObject() };
    ac.first_signal( item );
    ac.output_signal( item );
    rac = ac.obj;

    // - find & correct decider combinator [train limit];
    auto rdc = res.find_unique( Item::get(names::decider_combinator) );
    auto dc = Decider_Combinator{ rdc.toObject() };
    dc.first_signal( item );
    // One wagoon has 40 stacks, so less than one wagoon.
    //qdeb << item.name << "has stack size" << item.stack_size;
    auto min_count = item.stack_size * 36;

    dc.constant( min_count );
    rdc = dc.obj;

    // - find & correct constant combinators [visual control];
    auto lcc = res.find( Item::get(names::constant_combinator) );
    for ( auto ref: lcc )
    {
        auto cc = Constant_Combinator{ ref.toObject() };
        cc.replace_all( coal, item );
        ref = cc.obj;
    }

    // - train stop name correction;
    auto rtrain = res.find_unique( Item::Named::train_stop() );
    auto ts = Train_Stop{ rtrain.toObject() };
    ts.set_name( item, "receive" );
    rtrain = ts.obj;

    //  gluk from blueprint
    res.remove_field( Item::get("wooden-chest"), "bar" );

    return res;
}
//=======================================================================================
static const char * rv2_12_wood_iron_template();
static BluePrint rv2_12_wood_chests( Item item )
{
    static auto loaded = BluePrint::do_import( rv2_12_wood_iron_template() );
    auto iron = Item::get( "iron-plate" );

    auto res = loaded;
    //res.icons
    res.icons.set( 1, item );
    res.icons.set( 2, Item::Named::virtual_signal("R") );
    res.icons.set( 3, Item::Named::virtual_signal("2") );
    res.icons.set( 4, Item::Named::virtual_signal("L") );

    // - set override size of burner inserters to 1;
    res.set_burner_inserters_stack_size_1();

    res.arithmetic_combinators_replace_in_out( iron, item );

    // - find & correct decider combinator [train limit];
    auto rdc = res.find_unique( Item::get(names::decider_combinator) );
    auto dc = Decider_Combinator{ rdc.toObject() };
    dc.first_signal( item );
    auto min_count = item.stack_size * 12 * 8; // 12 chests, 8 stacks
    dc.constant( min_count );
    rdc = dc.obj;

    // - find & correct constant combinators [visual control];
    auto lcc = res.find( Item::get(names::constant_combinator) );
    for ( auto ref: lcc )
    {
        auto cc = Constant_Combinator{ ref.toObject() };
        cc.replace_all( iron, item );
        ref = cc.obj;
    }

    // - train stop name correction;
    auto rtrain = res.find_unique( Item::Named::train_stop() );
    auto ts = Train_Stop{ rtrain.toObject() };
    ts.set_name( item, "receive" );
    rtrain = ts.obj;

    //  gluk from blueprint
    res.remove_field( Item::get("wooden-chest"), "bar" );

    return res;
}
//=======================================================================================


//=======================================================================================
static QByteArray rv2_6_wood_chests_coal_template()
{
return R"(
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
)"; }
//=======================================================================================
static const char * rv2_12_wood_iron_template()
{
return R"(
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
)"; }
//=======================================================================================
QByteArray PR_Trains_V2::send_mine_12_iron_template()
{
return R"(
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
)"; }
//=======================================================================================
QByteArray PR_Trains_V2::send_mine_6_iron_template()
{
return R"(
0eNrtWl2SozYQvoue7QmSkABXNpdI3ramKIxljyqAiICZuLZ8gNwjJ8tJIoF/MJZsiZnsVk3lZTxg8an19detbplvYF10rJa8asHqG+C5qBqw+voNNHxXZYW+1+5rBlaAt6wEC1Blpb6SGS/AYQF4tWF/ghU8PC8Aq1recjY831/s06or10yqAecn806+ss2yB1iAWjTqGVHpiTQOQQuwB6slCpBC33DJ8uHr8LC4AUVn0KZVeLuX1gpLBliYJNewxACLXW2NT6D0GjQygIZX1C3zl4xXyyPJt9AUPp0tpk/kGh4Z4Im3zeE1KDWA0jNoIXJRipa/MpOx9ISpDRWSK5hsGBA8RcoyLZ1Gj86FlpSmossLlsnltmOFXpBh8sjZuRSP539AVOwOSzxgE3fYyAMWBu64iQ/uKB4zuRPLt2ynxt6iRviOb5H2bfWqbgmpBlVdUZjmcg/TCPqsAbvj+igEhu64PhKBxC2c4uAR5XPCCVL3VXkp1D1OIy+Fugdq7KUa90iNfVSDghmbEXy8byA4e+PA043DlOPRJTp51TDZqpumpHUH1rg145HYd7xpea5MZ40ihf3Rqc+H06B+muPodMsL9chQWpxqjvMMV/JfqLDodDWjahKTYaPoLrOiWBZZWZtMia9XbIIabbqqbGqzql2quF7zKlMJ8QEmutnVteFVK0WRrtlL9soVhHpuvPCbmuyVy7brdXBaUj9iSXVpdqJhVKQtHtZ1XIpqKSQzA2hKTURcckvJNrwrl6xQy5LK57UojCVDMtWTWns1UNGnNqj/7CRj1bia5Bs1mUo4OZd5x9v+Go4M0td4MBJUTMXgWnQ9dyE0auGSuzLJ25eS9TK968KR4ehgdtkFK1Vfb/h5UVsulZQ9PNAwDZCe1KVmVUyLmsnjfgB+Us+Jrq07D9iDF9tURxFA1gGkp9tE7iWBbzMV93eySwR9s0vijh14YuNLIn8TYsOqIW89MBtZRSzZ5oYzpNslI534Rs6hhV8Mne0M5toJ7XYGEzt7oRjtRO6+Qr6+wu7Y2Bc7dOYXzeWXuPOLiY1f4mwnnmsntdsZTu1MbHZSd18RX19F7tihL3bszC+Zy29i5zeZ8Bva8i1OnO0MZ9pJA7udZKqD2GJnGLgVYBG9ttIEBX3rjjGoZ92hFjTxBJoWIrd1B6KmuiO8pMQNy/mGyftFx6UjxI5V4xH2vfXHpfBAQRDo67LOZG/lCvzsXHvofkj1LK2oB9B6n/a1ZbqVokx5pSDAapsVDfOqTfpQuFebhNimQeyowcQQKTdkn0RwJtuZ6ykxJ7anVH/RX3cNU1MUQgurlR1zj9vQnr+nIkYTkVNbuglDl74xij2zbUjm9I1R/J/3jSH1bPbi4Ds1e+siy3839mvI2PD54+APwgk/CId44eT7rLK3s+5BZE0mkSme7x0nYScxNEy1fq1Ie9BjflwMU6R6ipptUmcSfhvayXZAa9KCl7wd8sgR83jPJ2VpyNPRJPiqx3057R7P2nr1VJlVypzJrNDEYuz5CxGM42sajajJ2PCqqYVsl2tWPGqTAnPBQQIPOHgN9/AkjsBZTS28Savv36VsKmKvTO7bF17t7u9X//z1Nzi4hxa295nT057p/qRbaWNUEjTr+OEzsGmv0sn0dIHYukqCPZSOfJUeeoBjX3Ay67zhMzg+tDv+Jm5sxzWEzjpS+Qz02U9jyLS71Z2wmb7IQ9qhr7RjD3DiC57MOp/5DI6PrY63+pkGs06cPgNb9sMqQqdZxnYYSKF/Aw5/YAP+y/sacGo/8Le2FRS9o+GE/zecP67h3LOiEG8f0HJaD18o9tUG/mBt+PxqbP7RmIa+a0DfSd+/WrStlqGiuMlf2KYrjq85Xt7k0dd0AcloyDDtgw75LRtnrgF1yD0sPRra03H8f9sVBRhOqKzIihU2vFvkCc7Kut1r9Ge90t7Hq9ELogugtpRm4DuGYZSgKIpxjDE9HP4FYd8XEw==
)"; }
//=======================================================================================
