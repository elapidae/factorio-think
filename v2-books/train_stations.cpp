#include "train_stations.h"

#include "blueprint_io.h"
#include "bprint_landfill.h"
#include "raw_train_stations.h"

//=======================================================================================
static auto water_pump_bp = R"(0eNp9kOGKwjAQhN9lfqfF9qzRvIrIYdvVW7CbkKTHlZJ3v9TCIaj3c5bZb5iZ0d5Gcp4lwszgzkqAOc4IfJXzbbnFyREMONIABTkPi7KXS/iyngo3Dg5JgaWnH5gqnRRIIkemFXQX06eMQ0s+G94gFJwN+cvKkplJjdZlozDB1LoqmxzRs6duddRJPZHrP7JjR0W0xdXbUfpX6N1/6NzgXtY8bKPwTT6shn211Yda73eHzcdmm9IvBB1piA==)";

static auto nuclear_fuel_request_bp = R"(0eNqFkd1uwjAMhd/F1ylqSqElrzIhVIJhllK35GdaVeXdl7TbhBASV5Ejn+8c2zOcTcDREntQM5Ae2IH6mMHRjTuT//w0Iiggjz0I4K7PlRlu5DzpQn+i84XFe0gvWogCiC/4DUpG8RbDQRvsbHENaB6kVTwKQPbkCdc4SzGdOPTnZKLkP4HYoc3GAsbBJcHA2S1B6lZudgKmhNs2m12iX8iiXjv2OdwTtHo/3QuT8snkt/l0JZMUa/q/jbyeW4AeQt6/jMc8+LIi9XAYAV+JtJhWraybQ9W0+0O5LesYfwCDdpUK)";

static auto rocket_fuel_request_bp = R"(0eNqFketqwzAMhd9Fv52S69L4VUYprat2Yo6c+TIWgt+9drqNMgb5JSR8zvkkL3DWASdL7EEuQMqwA/m6gKMbn3Se+XlCkEAeRxDApzF32tzIeVKFekPnC4sfIVW0EAUQX/ALZBXFpo016h19cQ2on5R1PAhA9uQJHzRrMx85jOeUIattDgGTccnAcA5Ppk3f7ToBc7Jvhl2X0r4fH6+kk+IR9MP+L6EAZUI+VBUPebk/VPWviNih3aJoy0SRN11PIp8+QsBn4llF9b5q+6Hu9y9D2ZRtjHf+Go+m)";

static auto four_crab_belt_bp = R"(0eNqllstuwyAQRf9l1jQymIfNj3RRVVUeKEJysIVx1CjyvxcnbRoltjrQlQX2nJm5XANn2DSD6bx1AfQZ7LZ1Pei3M/R279bNNBdOnQENNpgDEHDrwzQKfu36rvXhZWOaACMB63bmEzQdyZ/BfdfYEIy/C2OzYUfrwxBnfiMvX7y83kWW4zsB44IN1lxLvwxOH244bGIOTZ/zEujaPga0bkoWIaIQBE6guSxXIrJ31pvt9T2fKntAMhRSpSDLJWlnwHz1U614RLMZNM9Cc0zVIgEtlqueQ8sbeogL7fe+jU8E/LlucnOh64bJq0+5VEIbarkNOYOustAo8esEtEwTnxZJ6st/qU9plosURn7KssyvUCKVqG1AfjMlismzFlVh9gEqsryI00Jm6Vyh2CpzK6iWzdgOYcmNVdJ5UaM6qLOUR6nDcn/VLHUYTTr6ZtSJp/XlNqDvbh4Ejsb3V+NWlKuaqUrWRVnwcfwCBWnM3A==)";

static auto four_crab_express_belt_bp =
R"(0eNqlluuKwyAQhd9lfttSR3N9lWVZepEipCaoWRpK3n21ZSFs062XX8Gg55uRc9QbHLpRDFoqC+0N5LFXBtqPGxh5VvvO/7PTIKAFacUFCKj9xY/EddDCmI3Ve2WGXtvNQXQWZgJSncQVWjqTYBEzdNJaoRfLcf4kIJSVVopHQffB9KXGy8HNbOlrFQJDb9zCXnmyrwV3zbYgMEG7qRl3lJPU4viYUfpC/4jjuz5XEJQuENviPYSlQHaREJ4CYf9A+AqkSIEUkZ2UKRAeCamiXEXLKFfVyZbF9+LNk/jokqTPunffID+xpw0iv7HtRzuMPt3PMdxlRsVT13Rpdj+Y1E9u9DEkMJRlxpKFmJnyODfjQj9AvcjsAYN6KON6KOJ6qNJcxoNSI9Urk9XZWEzBNsmnW8ABhLknAQ3xA9LMWzOMgpnepuunGrLMmzKsep55Va5Q3Gvs/nZrF+9FAt9Cm/sErCmvGqzq2m1DVc7zD4VXYso=)";

static auto feed_sources_belts_bp = R"(0eNqdlOGKhCAQx99lPttSZpo9wL7EsSy1K4dQFmrLRfjuZwVLHN2SfnOG+f/mL44zQ9OOYtBSWahmkI9eGai+ZjDyW9XtkrPTIKACaUUHCFTdLZHVtTJDr23SiNaCQyDVU/xAlTkUL8aH4pfUdvSZt36rSK47ZR6kxDslcTcEQllppdiuvgbTXY1dI7S/0X++EQy98bJeLS09KmHsUiCY/Cln6aXwTZ5Si8dWQhaLf9g4gE0/sOkBOw9gk0A2CWAXgewigF2+2ZSfYdMANv/APnpLFjUn53yXUXNyzjePestzvrM0agiP4P6Xrluk2m0sBC+hzVqAy4wwjllJeZqnxLlfkuaTRQ==)";

static auto feed_belt_bp = R"(0eNqdlNFqxCAQRf9lnu0SjSYmv1JKSXZlERINxpSG4L9XN1BKsrbWJ1Hmnpm5DrNBPyxiMlJZaDeQV61maF83mOVddUN4s+skoAVpxQgIVDeGmzWdmidt7EsvBgsOgVQ38QktduhP8eJDzd1ofx7lJEEezV26NwRCWWml2Lt4XNZ3tYy9ML64GAPBpGcv0ypkDShWXBiC1WsovjCf4yaNuO4RNBR5QJMsNElBl3HjfoWXJzj6NlRNS3DulItmtcFS2mBZaJqCrrLQVQq6zkLXRzR5gub/QOM4+lnVTebI8PjI6MVGZgYXWR41KY1gnGUST2KTLPap7iqsnceKan9sUwQfwsz753P/bQ2pedUUZUGd+wIuIcdx)";

static auto six_wooden_chests_bp = R"(0eNql1c1ugzAMAOB38TlUECCkvMqEJgpWGykJiJ91FeLdl7ALRaFr2AUpKLY/Y8lMcJEjtp3QA+QTiKrRPeQfE/Tiqktp3w2PFiEHMaACArpU9nRvmhp1UN2wH2AmIHSN35BHM/kzVGEtRhWgxGroRBW0jcRVCvpGil6VUgayVO0qMH4j8NqhUd9Ft66YzAUB1IMYBP42vxwen3pUF+xMV67CBNqmNyGNttVsfcZOKYGHuZ9Ep3S2nE0i+vojOFJmTykJmPloEyKWMU0Q2cfS1Not6qUpIwCN4nq7NGNnG4vCwoGK3UN92V/siyFPZ2ZxDkpygEL9KHRDiXco6QFK6kdhGwrfobADlMSPEm8o6Q4lO0DJ/Ch8Q4nCHQs/YGF+lnRjyXYoZ+8Fwd0LIgr/sSG4X3OZY0PQwu7CZWfmqz8DgS/s+qUq5WaiZ5pxdg7jMJnnH2MJEaM=)";

static auto chests_with_quick_manipulators_bp = R"(0eNqdlmFrgzAQhv/LfbaliSba/JVRRltvXWCNJUm7lZL/vqgwRJQl90WI5H3uvbsX9AWnrzverDYe1Av0uTMO1NsLnL6Y41f/zj9vCAq0xysUYI7X/vRxdH6jjUPr0UIoQJsWf0CxUPyr/e66Fs3m/InOT6R8UfrQ1t/jmz/1eGPDJsoyS8knyiocCkDjtdc49j0cnu/mfj3FxhRb6biAW+eiqjN9xd6DFFtRwDNKKr4VsUSrLZ7HG0NrMzKnkMsUcplOrvPIFYWcNA2xnI4FsJxZjok1I9n1d1j/uFhEM12nbkHJSdn+zHg4hLDgRRK88DwvYqV0TQlFlTLghkIWKeQ9JRRJZLajoJPGwRhhySJvyYzPE9esrJ1xgpsqN3IzM2zNTEmJikyaekVB10loQclKGlpS0GkDqQmLrzNjuJq6hlBcZhZn89jVg5v42R1+CtTk/6OAB1o3zqqJbe553cj9rtxVIfwCZYDR3A==)";
//=======================================================================================
// This is template where:
// - six wooden chests
// - decider combinator has [coal]->[tran-stop];
// - two const combinators control two lamp colors -> red, green;
//      with four views [R] [coal] [coal] [coal];
// - train-stop controls by decider combinator;
static auto R_coal_tmpl = R"(0eNrtWdtu6ygU/Ree7SMDvms6HzGat6PKcmzSIvkmjDOnqvLvB+xcne0WiEaah3mp5AQWi7XWxpv0E+2aiQ2CdxLln4hXfTei/OcnGvlbVzb6M/kxMJQjLlmLPNSVrX4SJW/Q0UO8q9kvlOPjq4dYJ7nkbJk/P3wU3dTumFADLjNHqea+vUt/hvDQ0I9qVt/ppRQSDTIPfaCcxPh49B5wyAVHw3T+KPsBAMH4AuIhtScp+qbYsffywHuhB42sqwvZFzMKyvdlMzJvwSw05sDq4kGCAxdyKpurCssI/2+txMjkgjYWDW+5klOK6Yx5+qz4RtWbPR0X4h2r9L5GPQXrP2+Cse5WYV6jPFJjuagmtYJ+JMdXPX2U5aIJ+qmXean6snkVrGL8wBCgLbX3iEIehRccnSZZdtKv+nbHu1Iq8SGzfkRnvB+RIl5zsWwb5TFs3543komNpG7Z9BeaNZ101PFNdL1v066VAyeTZybTZyaH4OStrS+pAbevSncjaoLV66ClOlmA5dFlwZpVvGbiG8eDi+PhRoGecAr1Xc0vvPZcjN9W0VWzJX1qmTAI9HM7lGKmlKM/1Ph+ksNkVZQaZPgoZhWLvejbgncK4nSAWNXsSXiyOYDc6Lxof/+cbXgR25dxBOEk7mUc/l/G/0oZ64p8voi3gpNel2vLpvGbsh2+Lt5o9hly9vw6upSvcfWuy+1cw+sCftFfTyNTSzS9zpB+3ZqLEOqOxfhlCqiVGaqF/xNq/fmcWsmzauHA/lRKQKBrJ9mymk+tzxq1AcErf+gb9nVek7MDTm0VXh3AOF76rI6p7ez6aT7IaPQKsSbWadFcISSHLi0Dga5t2r4cpa+aVCbUafy1gunDyQ5BRy7QmRH09e32T9/XrPOrdzbKr6VM7WzHD0YnW6lOHNhklmziFRtCt9ik5rITS0czF2gjR4n9yZDAV0PskLokMOJIXKCxETS1j9CJtHmEknWEwo0IkdCBDbZjQ+iKDcVbbCKH1Bk6GrtAmzma2AcavEeT1CV11Ihj5gJNTKBp4BAhahchuj6habQRIYod2BDLQIdrNsEWG+KSOjPZqQu0UVhoaB9osHehkXvvloSWEQmA5gxjqDmjsW1zNpOBkBxKH+xyaWoPBHZ5NLMGSsG3a3gt62oSB1ZvwqQnmPg+WREEiu9+UFa1Od9mlisPAJ2cDUgJbEBIDFnq+wjEMoRAqRXLa2bTh8oF4UNTZckCm5F7UAKBRua+n9lm97AUgjX/cUlfVCBYMAeJqW0xLMF8P51vxvnNPzQ8dGBiXDRKcZhkJEnjLKBBeDz+BsiLO4A=)";
//=======================================================================================
static BluePrint R_coal_replace( Item item )
{
    static auto coal = Item::Named::coal();
    static auto _bp = BluePrint::do_import( R_coal_tmpl );
    auto res = _bp;

    //res.icons.replace_all( coal, item );
    res.icons.set( 1, "train-stop" );
    res.icons.set( 2, item );
    res.icons.set( 3, "signal-R" );
    res.icons.set( 4, "wooden-chest" );

    res.train_stops_replace( coal, item );
    res.constant_combinators_replace( coal, item );

    auto count = item.stack_size * 8 * 6; // half of wooden chest * 6 chests
    res.decider_combinators_replace_first_signal_count( coal, item, count );

    return res;
}
//=======================================================================================
BluePrint_Book Train_Stations::R_solid_intermediate_stops()
{
    static auto bp0 = BluePrint::do_import( four_crab_belt_bp );
    static auto bp1 = BluePrint::do_import( feed_belt_bp );
    static auto bp2 = BluePrint::do_import( six_wooden_chests_bp );
    static auto bp3 = BluePrint::do_import( chests_with_quick_manipulators_bp );

    auto fn = R_coal_replace;

    BluePrint_Book res;

    res.icons.set( 1, Item::Named::train_stop() );
    res.icons.set( 2, Item::Named::vsignal_check() );
    res.icons.set( 3, Item::Named::virtual_signal("R") );
    res.icons.set( 4, Item::Named::virtual_signal("V") );

    res.add( bp0 );
    res.add( bp1 );
    res.add( bp2 );
    res.add( bp3 );
    res.next_line();

    res.add( fn(Item::Named::coal()) );
    res.add( fn(Item::Named::stone()) );
    res.add( fn(Item::Named::iron_ore()) );
    res.add( fn(Item::Named::copper_ore()) );
    res.next_line();

    res.add( fn(Item::Named::iron_plate()) );
    res.add( fn(Item::Named::steel_plate()) );
    res.add( fn(Item::Named::copper_plate()) );
    res.next_line();

    res.add( fn(Item::Named::electronic_circuit()) );
    res.add( fn(Item::Named::advanced_circuit()) );
    res.add( fn(Item::Named::processing_unit()) );
    res.next_line();

    res.add( fn(Item::Named::plastic_bar()) );
    res.add( fn(Item::Named::sulfur()) );
    res.add( fn(Item::Named::battery()) );
    res.add( fn(Item::Named::explosives()) );
    res.next_line();

    return res;
}
//=======================================================================================
static auto S_copper_tmpl = R"(0eNrtWV1vozgU/S88kxH+IEC0M39i921UIQpOagkwY0y6UZX/vteQBEpMYtPRah/2pS3FPvf43OPLxXx4r2XHGslr5e0+PJ6LuvV2Pz+8lh/qrNT/U6eGeTuPK1Z5vldnlb6SGS+9s+/xumB/ezt0fvE9ViuuOBvm9xentO6qVyZhwG1mKXJRCcWPDNAa0cIUUes4AEOCxPdO3g5vKWALyQElG+4Hfs+g1SNzoZkhfD77d4HwLVCrgOThTW16rg9iIRMOueFomHrTKtEYQBC6gfjAq1ZSlOkre8uOXEg9qGV1kSqR9ijebp+VLfMHzFRjNqxI77Q+cqm6rBzlHkZs/vKAKizsoon3U0vyPdcociMke9HRYFaV1TB9iNmmJa+40jm6XyV1V4uY1ApvOAXLeQFsIMmvvM4UqGBQLfgWThJt0u2Ck8K9op/bZ37PZavSJ94c9fAGcBBM2xsHQaCvqyaTPbGd9wfMEp1quqegExf0oM0JqHW1SvdSVCmvAeKS3fMQtGb5jTbSPw6SsXq6N3gBSaHnFxiPFwckE7X7CQFMMKVgO1n/sOInOUC3HJBvIXAouBwo91imnOx5qZhcqA9Lnv1z0KvTGUCTguE/rTHzPM4g8NchyNchqBFiSQxdbM16oN4HJt9IVtybwuyByH07hyaceL2X6P9e+pe8dGJlKd5/g5sWS0oyhqyystyUWdU8ruZhn31TvnMu846rsZ5bl/N55b2W83kt/65vdy2DEKXQzlKyY/YqbHULYyzBsLgre32JF9RCgaVc6D8h14+vyRV/WS7kXqwiI9DY8kG3wySUlccm3c5LFDahkknHeuCt4vkmf2MtkGS/OvjNnhTCIcplcDotd9dNegtQd3nJMrnZd0wv/7qd9R6+5zW2bBUreFdtWAnrkECvESV7vPLo6je75mSWSTRrRXBfN4AOg+S9iq5fHsVG1qHz3tBcTUiTPieTB7F5zw4wf9k0ETK9StRHuBYSBtRdWZrirHiWJkbC48N0n4F97DwaW3k0WQOd2EDjsZi9C1GwejD/45TFbvZCdG4otFArMFrBJnFjA26esYmW2GB72bFbRjFZA22XUfd3vcj4ZozDFa6LkBXH7RrowAo6crfQBdneQncVMl6yULyCDXJkE83YELrEJlnhOjvZSbAG2sosxL2BiIyHFwSvcR224kjWQBMraLrCQtjRQvHcQuGChUi4gg1xY0Pmzwu61FuS7RrX2ckerYG2M0vsdkgaxXedjQ5odUxKEvfNY+zHaODWfUehjRQUfa37vkT57d03xeu774g62j00tNeIGmkR1/a6J2NCWtElGN/KaOgOZOyf6dYZKDb2LXTcuXknj6xYhIkvMNvPRg1NoPGnTyJg0v7te3hFN0BH1wTEeCEBiSVLfdxgYklNx/OBE8vRs/Fd4TLCI1tl8QCb4OclIHT4knNlm3yGJSZYYg2rjwBMsCYfhNQ2bVuzBJE+T2mhxhVdefmENj4E+p3vk3gyZDg4ffol6D2bHiINuMMxEEsvx0f9ie7l7z28DHtD5XuADaTZ8GhyhGdVo04a/0Wvtj+32k0+QPreEar04IgY0SiBR9w2CUhAz+d/ACyad7s=)";
//=======================================================================================
static BluePrint S_copper_ore_replace( Item item )
{
    static auto copper = Item::Named::copper_ore();
    static auto _bp = BluePrint::do_import( S_copper_tmpl );
    auto res = _bp;

    res.icons.set( 1, "train-stop" );
    res.icons.set( 2, item );
    res.icons.set( 3, "signal-S" );
    res.icons.set( 4, "fast-inserter" );

    res.train_stops_replace( copper, item );

    //res.locomotives_init_fuel_coal( 150 );
    res.schedules.replace( 0, copper, item );

    res.constant_combinators_replace( copper, item );

    auto count = item.stack_size * 40; // one waggon
    res.decider_combinators_replace_first_signal_count( copper, item, count );

    res.locomotives_init_fuel_coal( 0 );

    return res;
}
//=======================================================================================
BluePrint_Book Train_Stations::S_solid_intermediate_stops()
{
    auto fn = S_copper_ore_replace;

    BluePrint_Book res;

    res.icons.set( 1, Item::Named::train_stop() );
    res.icons.set( 2, Item::Named::vsignal_check() );
    res.icons.set( 3, Item::Named::virtual_signal("S") );
    res.icons.set( 4, Item::Named::virtual_signal("D") );

    // for inserter templates.
    res.add( BluePrint::do_import(four_crab_belt_bp) );
    res.add( BluePrint::do_import(four_crab_express_belt_bp) );
    res.add( BluePrint::do_import(feed_sources_belts_bp) );
    res.add( BluePrint::do_import(six_wooden_chests_bp) );
    res.add( BluePrint::do_import(chests_with_quick_manipulators_bp) );
    res.add( BluePrint::do_import(rocket_fuel_request_bp) );
    //res.next_line();

    res.add( fn(Item::Named::coal()) );
    res.add( fn(Item::Named::stone()) );
    res.add( fn(Item::Named::iron_ore()) );
    res.add( fn(Item::Named::copper_ore()) );
    res.add( fn(Item::Named::uranium_ore()) );
    res.next_line();

    res.add( fn(Item::Named::iron_plate()) );
    res.add( fn(Item::Named::steel_plate()) );
    res.add( fn(Item::Named::copper_plate()) );
    res.next_line();

    res.add( fn(Item::Named::electronic_circuit()) );
    res.add( fn(Item::Named::advanced_circuit()) );
    res.add( fn(Item::Named::processing_unit()) );
    res.next_line();

    res.add( fn(Item::Named::plastic_bar()) );
    res.add( fn(Item::Named::sulfur()) );
    res.add( fn(Item::Named::battery()) );
    res.add( fn(Item::Named::explosives()) );
    res.next_line();

    res.add( fn(Item::Named::engine_unit()) );
    res.add( fn(Item::Named::electric_engine_unit()) );
    res.add( fn(Item::Named::flying_robot_frame()) );
    res.next_line();

    res.add( fn(Item::Named::stone_brick()) );
    res.add( fn(Item::Named::concrete()) );
    res.next_line();

    return res;
}
//=======================================================================================
static auto R_water_replace( Item item )
{
    static auto water = Item::Named::water();
    static auto _bp = BluePrint::do_import( raw_fluid_Receive_water );
    auto res = _bp;

    res.icons.set( 1, "train-stop" );
    res.icons.set( 2, item );
    res.icons.set( 3, "signal-R" );
    res.icons.set( 4, item );

    res.train_stops_replace( water, item );
    res.constant_combinators_replace( water, item );
    res.decider_combinators_replace_first_signal_count( water, item );

    return res;

}
//=======================================================================================
static auto S_water_replace( Item item )
{
    static auto water = Item::Named::water();
    static auto _bp = BluePrint::do_import( raw_fluid_Sender_water );
    auto res = _bp;

    res.icons.set( 1, "train-stop" );
    res.icons.set( 2, item );
    res.icons.set( 3, "signal-S" );
    res.icons.set( 4, "coal" );

    res.train_stops_replace( water, item );
    res.locomotives_init_fuel_coal( 150 );
    res.schedules.replace( 0, water, item );

    res.constant_combinators_replace( water, item );
    res.decider_combinators_replace_first_signal_count( water, item, 25000 );

    return res;
}
//=======================================================================================
BluePrint_Book Train_Stations::RS_fluid_intermediate_stops()
{
    BluePrint_Book res;

    res.icons.set( 1, Item::Named::train_stop() );
    res.icons.set( 2, Item::Named::virtual_signal("R") );
    res.icons.set( 3, Item::Named::water() );
    res.icons.set( 4, Item::Named::virtual_signal("S") );

    auto Rfn = R_water_replace;
    auto Sfn = S_water_replace;

    res.add( BluePrint::do_import(rocket_fuel_request_bp) );
    res.add( BluePrint::do_import(nuclear_fuel_request_bp) );
    res.add( BluePrint::do_import(water_pump_bp) );
    res.next_line();

    res.add( Rfn(Item::Named::water()) );
    res.add( Rfn(Item::Named::crude_oil()) );
    res.shift_to( 3 );
    res.add( Sfn(Item::Named::water()) );
    res.add( Sfn(Item::Named::crude_oil()) );
    res.next_line();

    res.add( Rfn(Item::Named::heavy_oil()) );
    res.add( Rfn(Item::Named::light_oil()) );
    res.add( Rfn(Item::Named::petroleum_gas()) );
    res.add( Sfn(Item::Named::heavy_oil()) );
    res.add( Sfn(Item::Named::light_oil()) );
    res.add( Sfn(Item::Named::petroleum_gas()) );
    //res.next_line();

    res.add( Rfn(Item::Named::sulfuric_acid()) );
    res.add( Rfn(Item::Named::lubricant()) );
    res.add( Rfn(Item::Named::steam()) );
    res.add( Sfn(Item::Named::sulfuric_acid()) );
    res.add( Sfn(Item::Named::lubricant()) );
    res.add( Sfn(Item::Named::steam()) );

    return res;
}
//=======================================================================================
BluePrint_Book Train_Stations::book()
{
    BluePrint_Book res;
    res.icons.set( 1, "train-stop" );
    res.icons.set( 2, "train-stop" );
    res.icons.set( 3, "signal-R" );
    res.icons.set( 4, "signal-S" );

    res.add( R_solid_intermediate_stops() );
    res.add( S_solid_intermediate_stops() );
    res.add( RS_fluid_intermediate_stops() );

    return res;
}
//=======================================================================================
