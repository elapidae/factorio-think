#include "pr_trains_v2.h"

#include "vlog.h"
#include "qdeb.h"
#include "items/arithmetic_combinator.h"
#include "items/constant_combinator.h"
#include "items/decider_combinator.h"
#include "items/trains.h"

//=======================================================================================
static auto items()
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
};
//=======================================================================================
static BluePrint rv2_6_wood_chests( Item item );
static BluePrint rv2_12_wood_chests( Item item );
static BluePrint s1_12_wood_chests( Item item );
template <class> class TD;
Blueprint_Book PR_Trains_V2::build()
{
    Blueprint_Book res;
    res.icons.set( 1, Item::Named::train_stop() );
    res.icons.set( 2, Item::Named::virtual_signal("R") );
    res.icons.set( 3, Item::Named::virtual_signal("V") );
    res.icons.set( 4, Item::Named::virtual_signal("2") );

    for ( auto && it: items() )
    {
        res.add( rv2_6_wood_chests(it) );
        res.add( rv2_12_wood_chests(it) );

        if ( !it.name.contains("plate") )
        {
            res.shift_to( 5 );
            res.add( s1_12_wood_chests(it) );
        }

        res.next_line();
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

    return res;
}
//=======================================================================================
static const char * rv2_12_wood_iron_template();
static BluePrint rv2_12_wood_chests( Item item )
{
    static auto loaded = BluePrint::do_import( rv2_12_wood_iron_template() );
    auto iron = Item::get( "iron-plate" );

    auto res = loaded;
    res.icons.set( 1, item );
    res.icons.set( 2, Item::Named::virtual_signal("R") );
    res.icons.set( 3, Item::Named::virtual_signal("2") );
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

    return res;
}
//=======================================================================================
static const char * s1_12_wood_coal_template();
static BluePrint s1_12_wood_chests( Item item )
{
    static auto loaded = BluePrint::do_import( s1_12_wood_coal_template() );
    auto coal = Item::get( "coal" );

    auto res = loaded;
    res.icons.set( 1, item );
    res.icons.set( 2, Item::Named::virtual_signal("S") );
    res.icons.set( 3, Item::Named::virtual_signal("1") );
    //res.icons.set( 4, Item::Named::virtual_signal("L") );

    // - find & correct decider combinator [visual control yellow/blue];
    auto rdc = res.find_unique( Item::get(names::decider_combinator) );
    auto dc = Decider_Combinator{ rdc.toObject() };
    dc.first_signal( item );
    auto min_count = item.stack_size * 40; // 40 -- wagoon size.
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
    ts.set_name( item, "send" );
    rtrain = ts.obj;

    // - correct schedulers
    auto sch = Schedule{ res.schedules };
    sch.replace( 0, coal, item );
    res.schedules = sch.arr;

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
0eNrtXFly4zYQvQu/pYRYCICuTA6RSuUn5VJREmyzQpEKFyfOlA6Qg+RiOUlAUgtFAWQ37MnErvyMR5b02HyN3h4Ifw7WWaP3ZZrXwd3nIN0UeRXc/fw5qNLHPMna39Uvex3cBWmtd8EiyJNd+6pM0iw4LII03+rfgztyuF8EOq/TOtX997sXL6u82a11aT5w/uamKZ/1dtkBLIJ9UZnvFHl7oRYnChfBS3C3pFQY9G1a6k3/Nj8sbkDpGbSqDd7jU+2EZSdYdg0bWWAZ1FZxAg2vQaUFlJ9BG0NZ+VgW5udyrbPagizoN9EJ2/zXoJ+ckO+bOrDAR2d4w0Re7YuydoLHF3DWgQ9MpxZsgcBWSGx5xn5IqnqZ5pUua/PGtNl0DG3YNSu3LotstdZPyXNalO33Nmm5adJ6Zd7bnsEe0rKqVzfr+zkt6ybJLku8/8RSP+vypX5K88d2vbfxUSdtsITti90+KZO6vVjw959/BYf+E3lvVtWik/afUm+HQZGaV0y0IfNYap2P31IDntrXhB7uDwcLeQpOnvpY5EkneXJMXuhiL4Yva0mQy5qEYNcMsT+AazhxuobQsW+EwzWEYLKlDKe8M587CYU7K/xYzgoRceTyFUPEEcPGEYe7hn0s13B3HDnDBtEFSIp1hYC7gn4sV0RuV4TjMOEu30hUSotAKa1oaldOU4ilEE24y7oUMKWTT9yJtakP/cBBllOCAJfICKEUAS6uLbfBMT84mK0cAY4dGCgmD2EnBipQgRRjJyl6CdRqn6W1PcWpYdcGMBoRjirERkzsBw6KGBZezfzLzVOS5stjSrbMxAO+QxA+8R2MydCd7kzIBirBLsmyZZbs9jZoeQ1tg7pE5E5v02a31Jm5tzLdLPdFpmdAezpsNcdaWti4A5OsLS3GAp0+Pq2LpmyFFi4Xkt3bbOVew2EIWXAs8praYdiX8P6tKLY6NytOV3M6BnFya6nn7uHxhnMe9pyvk3JU7M/2SrC9ytNe5bZXjOxlbNZe5TXswHwXe029IGweQnkemo3iudVZoES3Y+400ZyADSa+BrvHNz5uTNsmdsZg6jVrwbzHvIYHGDYHE818iXYPYzwaEy1niY7ABlNfg93qIuf4pSxgJXTYjjtKKJfYEjoERZbQm1tV0lJCTVVX0lZC+SVVnmbJpZkj12nezZHTzWZomdpsc+9Dmpk4cOy5uAbdH/r5tmmHW3LehOnaKzDGT1YMhsKgVoxer7bwGft27sBWLwqRDlPkjR12vUmWlkW+3GdJre082WmKiF87TyDtdkQxPlA3HcC8D9C7Z0Rdmy1sqBy81SfICTcG0BHBcRkGV8BxIwyuhONKDK6C48YY3BiMKzF+EyEcF+M3QeC4GL8J+Fa1xPhNMDguxm8CHm8K5bcIv2VPovnddSF8VQoix2nTln/EJe7WTZnrcnLmpRPo/wH5+5NT/LZ2USLum6bCwJfpVq8M7OYXY9Yfuq1hFrKUp6RDBEihE5ekkhWPaVWb5rHroJel/rUxP+1eicbXgTNwbBuP8KthC3Cq5WeT8maT6aRcPjS6ddGp6h9sHaa8pLGp9RRNrScbLAFKXuKaEhvUJXElZVo/7XTH9lRTNdC8iAAt/gvyZf1XEwEw1WVVuoVYXVb/st3eLfbarP7OhuBb89W+f8Ego0Kmk+oWAXV+wP1UgnyNxnhcHnA72x73mHk6s27lpJEGKTADlPTSILubsKF5qY5ONOGh200kDqs84xaU5A2zs7KBlB7KKM7iOHYbPFbA1KxsIL2kRqfDvMRFF5oKPdQ5rPvdqpEaR5qalecU8RBAsRYzt//H0rialcYV9RH9nB5jPvKkE81HNESyOSHPqsihTE2w6aMaYv3vjn81FpQVn7UYLxu62hD1GtkQWxUVv5V0R/cej+vmbVU0hZxbq6JSQFqkxY2vGhyuu5t2/jIzUl3sZ8eFRdBU2lwiK9pbq8tGI2qKuwiOabx5PtD5pJO6FIOt3pihpJxRZpWzgXbIfEfY1zekF2JjEY65/Q7ci469tX9ZdaPF6qEsdqt+Vrp7SLJKozrVLu9Mdapq/DRyHLmepw19xjIpvMeymH+hsSwmkLFsaDloLIspdj/hpvP8QvsJ68xM9G+wp+DGYW+Ew98IJ0Lh9MvPquF3Kwi8k69cscM8t0aAkknMEfqVjD+UfhWHSP0qjmxZd0r5lKDQrHS+XdXFqgM9JutFf4lVe4m93sLJ+rEXO+oerVpl6S6t+9p8xDz+DlNYUJXjpnh3LBtyjzrLz+11Pl2K4b3hR6fP2ro+BfZ8GBk9dWd1pPQVIiPYZleM3SEeajX8S2Z04thxfP3urr0i4DY+HTufceyl8ERv0hz/yw+VSznxUPlNIxwy12PlYeh18s+y+qzoxOvsHxSdeumD79Pf7idy4nisBdLpuUg5FwPzUtzeJaGKwAntpDgHZdxLVnyflIUTOYfdcBY7OYs8j+dZa97s8bxQeJ3UhCYh6XVoCoquvE7HQdFjL4X1fS7eqVNY/EY5ch5XxBzNZe+ds4lDhO7wRp6+jUDhPXFUjVCvs2pHl8zFCOp8Kkejcz90bte5CeoIp8TmCyLw0nP0FaXn718nPRPq7hGcUgwh0uvcHdQFyg89giiMBHUyEz0NoI5moqeBwdlMvDwa/S+Pfj15tA2914uj7t0eQqmvPAoUcghlns9FX19h4m9McK+nuvtCYZJYl0DvBn+taRGYnqHq17oiXMZUSsUUY+Jw+Afndmry
)"; }
//=======================================================================================
static const char * s1_12_wood_coal_template()
{
return R"(
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
)"; }
