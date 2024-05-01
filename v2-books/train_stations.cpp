#include "train_stations.h"

#include "blueprint_io.h"
#include "bprint_landfill.h"

//=======================================================================================
static auto water_pump_bp = R"(0eNp9kOGKwjAQhN9lfqfF9qzRvIrIYdvVW7CbkKTHlZJ3v9TCIaj3c5bZb5iZ0d5Gcp4lwszgzkqAOc4IfJXzbbnFyREMONIABTkPi7KXS/iyngo3Dg5JgaWnH5gqnRRIIkemFXQX06eMQ0s+G94gFJwN+cvKkplJjdZlozDB1LoqmxzRs6duddRJPZHrP7JjR0W0xdXbUfpX6N1/6NzgXtY8bKPwTT6shn211Yda73eHzcdmm9IvBB1piA==)";

static auto nuclear_fuel_request_bp = R"(0eNqFkd1uwjAMhd/F1ylqSqElrzIhVIJhllK35GdaVeXdl7TbhBASV5Ejn+8c2zOcTcDREntQM5Ae2IH6mMHRjTuT//w0Iiggjz0I4K7PlRlu5DzpQn+i84XFe0gvWogCiC/4DUpG8RbDQRvsbHENaB6kVTwKQPbkCdc4SzGdOPTnZKLkP4HYoc3GAsbBJcHA2S1B6lZudgKmhNs2m12iX8iiXjv2OdwTtHo/3QuT8snkt/l0JZMUa/q/jbyeW4AeQt6/jMc8+LIi9XAYAV+JtJhWraybQ9W0+0O5LesYfwCDdpUK)";

static auto rocket_fuel_request_bp = R"(0eNqFketqwzAMhd9Fv52S69L4VUYprat2Yo6c+TIWgt+9drqNMgb5JSR8zvkkL3DWASdL7EEuQMqwA/m6gKMbn3Se+XlCkEAeRxDApzF32tzIeVKFekPnC4sfIVW0EAUQX/ALZBXFpo016h19cQ2on5R1PAhA9uQJHzRrMx85jOeUIattDgGTccnAcA5Ppk3f7ToBc7Jvhl2X0r4fH6+kk+IR9MP+L6EAZUI+VBUPebk/VPWviNih3aJoy0SRN11PIp8+QsBn4llF9b5q+6Hu9y9D2ZRtjHf+Go+m)";

static auto four_crab_belt_bp = R"(0eNqllstuwyAQRf9l1jQymIfNj3RRVVUeKEJysIVx1CjyvxcnbRoltjrQlQX2nJm5XANn2DSD6bx1AfQZ7LZ1Pei3M/R279bNNBdOnQENNpgDEHDrwzQKfu36rvXhZWOaACMB63bmEzQdyZ/BfdfYEIy/C2OzYUfrwxBnfiMvX7y83kWW4zsB44IN1lxLvwxOH244bGIOTZ/zEujaPga0bkoWIaIQBE6guSxXIrJ31pvt9T2fKntAMhRSpSDLJWlnwHz1U614RLMZNM9Cc0zVIgEtlqueQ8sbeogL7fe+jU8E/LlucnOh64bJq0+5VEIbarkNOYOustAo8esEtEwTnxZJ6st/qU9plosURn7KssyvUCKVqG1AfjMlismzFlVh9gEqsryI00Jm6Vyh2CpzK6iWzdgOYcmNVdJ5UaM6qLOUR6nDcn/VLHUYTTr6ZtSJp/XlNqDvbh4Ejsb3V+NWlKuaqUrWRVnwcfwCBWnM3A==)";

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
static auto R_coal_tmpl = R"(0eNrtWMuOmzAU/RevySjY5hV1+hFVd1WECDgzlsBGxqSNRvx7bSAv5jKDk1bqoptIgO/xucf35byhXdmyWnGh0eYN8VyKBm1+vKGGv4istO/0sWZog7hmFfKQyCr7pFXGxarRskadh7go2C+08TvvU8Ncmo8XEwyaHLjSrXlzthpWrL5dWZIFm/2UsmBilb+yRl+Z0m7rISY015wN3vYPx1S01Y4p48iFbqsOrFgZby2bWjbGRgq7oaUQhh46muWYGvCCK5YPX3tuE0x8ccaK9/KqZ1GTETW6RfUBVLIYNYpg1AhApQv9j9ew/yGAGSzEjPCASdYdgBIuRaFnlE81jM6YFsxESx/aQ2QByP5TMGKTpwDiGLvh0Ru8G7YUQE+WnzgZcUGW/todKAKBfHegBAS6SpEqK8tVmVU1hLI+KUZ9+AT8S1pUrOBttWKl0VTxfFXLkn14qj2mZ+qUEMMxNHaNb39eFGPiul7wwhiE3dZwQIIZz3eyVbai4GAL0aLOSlEf9C+AS9yHWhFnv7zbF4l1FGIT3sEGO7IhUzbBHJvIXWQCAsV3uBU4upVM3MJ4zq3kDjbUkU0wFTmeYYPdiwcFMxX7d7gVubmF8VTkudjB+A42oaPI8ZSNP8eGuIsMVmhMnQtrDBdWHDxQWGPHY/MnQhETdDlXecv1oCRQeH0CFV4cuisJtigcXQ2yotGZ0KtcVjsuMi3Vh5IG/rS7414MrWSZ7thrduAGwZjteamZmpnCP5yMc9naMd6/ayB/Z4wfMSaPGFOnS4FiBey8jQ843qzJNNpmS13smjzB+hTo7872FL7mW3G23nPV6NTpwnUKPrSxOSGrOlN9AG7QV/u5bZjZopQ2irRqmYMMkb0bgfk4Tb+5ToWThYL5/4Rgz48JRvDDgpFLMy1YzgumPqkpF+Hw5L4AiziiXkRsFqt4ydGTfhRPBPxiVstW163zkdTHtM/adK9klXJhINBmn5UN65waRdAnOp5f8G7KmvZgQufOxv1yE4AjO8H3dw78v3P8lc4xBMsf6B1zNyPiPsEF4F2EUCiJoNIwogSLCkPDRJFqmfaYY+p5ww6p3aFmRbpYze9WyYbpAa1JS15xPZTTEXN851ImXOoAWG8NJZ0NIqAfdp9nGzxbowzjB4YgrQP3QzPDsukCvRubq39UPXQw+TikbGyG8wRHMU1ImIRd9xvtHh1J)";
//=======================================================================================
static BluePrint R_coal_replace( Item item )
{
    static auto coal = Item::Named::coal();
    static auto _bp = BluePrint::do_import( R_coal_tmpl );
    auto res = _bp;

    res.icons.replace_all( coal, item );
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
static auto S_copper_tmpl = R"(0eNrtWF1vozoQ/S9+Tqpg8xlt75/YfVtFiICTWjI2Mia9UZX/fsdAEkJNipNq9+W+VA3g4+Mzc4YZPtCWN7RSTGi0/kAsl6JG698fqGZ7kXFzTR8ritaIaVqiBRJZaX5plTGxrLWs0GmBmCjov2jtnRZfLsxlVVG1rHim6WApti49MKUbuHJZ3T2x/DlYSWZs+i5lQcUyf6O1Hiz1T5sFokIzzWh36vbHMRVNuaUKDnSl3agDLZZwasOmkjWskcJsaHDi1QId4XHsA3jBFM27uy23ESaeiZn4dszQgkmuApnA7N/0JFPSo0a3qJ4F1Z+Nmnh21MiCGszVNOwwyepkQQnnosQXlC/PG10wDRhkS5viXWZZkIOXoMcmL4GNY+yGF9/g3bD1LejJBZ3LXJZSswO1wUY9aAyQUjFAybr7kLPGJbV5MpfGPb7tFN5qfnKd97LK4XnuQJEVCLsDJVagq29KWrCmXFIOkiuWLyvJ6d2g+14bJKiXootSq6Nn/uwVpWJYTlgBC8LTBjggQYHvVjbKFBwcbmy0BsYrM86XPCsrGxn/howNKXBWyvesQKG9lt4lhR0VGlbL9kJkJLOxiR5gQ5zjdcsGr6bYXH2eZ2ovl+/ZHhjckTj4ZEXDkokDXJEKHhEN57adEvdwEhtlvHpAQN9RwGgsoDchIPYeYBO4sYHojdj4U2zcq4tvNR8mDxwrcjyWPz5WOHUs/wE2oSMbMjvkDxQm67sAh0+U8PjJ4xGwUc5U3jDdpbylxHvEVuJx5FziY3uJx7FbHxB4L0kSrhISTVSh25bAXj4eqEPWFzC51qGC5qyAwQCOsGUigzp4N3YBHnVIbRy1kjzd0rfswGA9LOpRU7hXsEuId0zVOnUcVMxkpDMzJvnY/CqrTLU01+gHrJKNrpovQW/HJtjiCNQaodOdkmXKBECg9S7jNT05ZaZx/QLhyQeIN05dMuFM4s3MzGsoVmcbfZL/bI6L/LPVHwt11n41kv7V3G5qCltwaQynVUMnpFO0+KRLYEZAu2Qjc+MpwQYDXU/ziyS+eDrwxo0+tuu4Y1xTNTGY3x2S2+xqB9knZvRPIPg7QMh3gPhO3w2OlHP5btfFay00N28m7UNcC/tftc8/T9oHP28f3/ldElhHFBI87kP8vw//qA/NN8fvcOFUe0lC96SydjokslnK9jbsUYJZbUlNRZFqmbaY/Qt/0e2Qmh0qWqSzxfyFTK9Qn7s49NuE7nUYsY3ZD9aVmQCAbtc65axk2v4ljMTu+kF3CrWghqmiaHj/OfXakZrfyQLHg0c6F82g/Z4Na2CH3FUxmvbatAbv/9/B8IxObdd9Fx2CRLte2XEDWlb6aHbYmBO3RlkPPqMv0AFqRFdGYhhbEhzFfkLCJDyd/gM7Jsp9)";
//=======================================================================================
static BluePrint S_copper_ore_replace( Item item )
{
    static auto copper = Item::Named::copper_plate();
    static auto _bp = BluePrint::do_import( S_copper_tmpl );
    auto res = _bp;

    res.icons.replace_all( copper, item );

    res.train_stops_replace( copper, item );

    res.locomotives_init_fuel_coal( 12 );
    res.schedules.replace( 0, copper, item );

    res.constant_combinators_replace( copper, item );

    auto count = item.stack_size * 40; // one waggon
    res.decider_combinators_replace_first_signal_count( copper, item, count );

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
    res.add( BluePrint::do_import(feed_sources_belts_bp) );
    res.add( BluePrint::do_import(six_wooden_chests_bp) );
    res.add( BluePrint::do_import(chests_with_quick_manipulators_bp) );
    res.add( BluePrint::do_import(rocket_fuel_request_bp) );
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
static auto water_receive_bp = R"(0eNrtWNuOmzAQ/Rc/Q4QNhIu6/Yiqb6sIEXCy1oJBxqSNVvn32pBANjskOKhSH/qSyI7neObMHHucD7QtWloLxiWKPxDLKt6g+PUDNWzP00LPyWNNUYyYpCWyEE9LPZIiZdxuZFWjk4UYz+lvFOOTBRjuipblo+WvVFJxZURAowMTslUzg1m/wv5xZek+s5132liIcskko32k3eCY8LbcqpUxHrfUQe7fpK2+tCd11SiriuvN9PbryEJH/e2ftCc3OATi6itIgAcQCyn2paiKZEvf0gOrhF7UUJ4nsko6FBTv0qKhVo+ZaMya5sls+n5qJhoqe7QmKVjJVOKlaC+Y57nEIP+945xmOq5Gm2D9sReU8muGVVpiX61lImvVDnpIThtt3si05wS9dul76bK2ETSj7EARwK5rnqUAypI34OjKlymXdlaVW8ZTqeiH0rXyL3grnbKciT5wFK/hBO5YoYKZUNXdOs+qVssSPymwL+Zkmbm7zNwzEnpfPSAJWBUNXHKC5rcFF+kKAxLvDxvmNGM5FQ/y7gx5DyeEesZJ1G85G/zaMdEAappmra9CFabvOI6eKOtUdF7F6JuyqFpZt0b61CD1MemITHaiKhPGFcT5LDGS75l7MrmAXFGtx+HNeCoda3M9RxBO8Lyew/96/ot61tJcruZwonzCcbsyLQq7SMv6fraj1dSFe7mfBh3fkfF90V2kfCvj7/rntqFqi6LSlaTv3/kkBLqFmX27AmxFM9ly/gm2Xpax5S1lCzvGZ1OAQaCxtSxpztrSpoUKQLDMrquC3s2ArtwFfRa+OYaxezNBnL4T41TFt63a7nwjZAOFQcz5cEE+rpu4SqR7aqsKeId4IAMPrhkPGIOBQt545mGBjT/2TeUVeCsYabwV67a893oI/NvLi0B44+1YsxosOHfwyZ/wKXyIQR5iROZUg907cZ6ooC99O1lST0pJcD0R84dkALY0hCw4Nvqm5pOqMYZUTcxfVCF4yhFzHYXg8UB8cyD4JT7KKGvFgeaTMGEPEzmfC8SHQEctaTQ7e+tus/7KA6CDS0rCNSwKEs70MnBgLz0INDLyciyczsuH8K4zl1ly9nn9+JRyDYRz9jZyP8O6EOz8aytwYVioDlx3btrWMAVdN9d1RvHVf3EWOqg3Rs9RiL0gIkG4jhzX8U6nP/ejiHg=)";
static auto R_water_replace( Item item )
{
    static auto water = Item::Named::water();
    static auto _bp = BluePrint::do_import( water_receive_bp );
    auto res = _bp;

    res.icons.replace_all( water, item );
    res.train_stops_replace( water, item );
    res.constant_combinators_replace( water, item );
    res.decider_combinators_replace_first_signal_count( water, item );

    return res;

}
//=======================================================================================
static auto S_water_bp = R"(0eNrtWNuOozgQ/Rc/QwQmXLUzP7H7NooQASdtjcHImPRGLf59bUNDOilISHakeZiXRIDruOpUnaLMB9qzltSCVhIlH4jmvGpQ8uMDNfRYZUzfk+eaoARRSUpkoSor9ZUUGa3sRvIadRaiVUH+RYnbWYDhgbW0mCzfM0nEhREGjU5UyFbdGc36FfbfF5beM9ttu52FSCWppKSP1Fyc06ot92pl4o6mjOe85JKeiIKreaNMeKV30nsHsYXO+j9S2FxQhZL1zx3LcNXolTnXvuFOe3q1D55C02Qe36St/tjSVj6E40E5uQUJ3RHEUm5VUnCW7slbdqJc6EUNqYpU8tSgoOSQsYZYPWaqMWtSpA+n6R+kXFWBDZSgHyYr30wydnonZVFmlTLt92tSRksqhxK6inC7nqkQYsofcXSVy6yStkrwnlaZVBRAlG38T7yNpq2gguT9igAm8UCZinBGQYs1nfNWS9B9Ukw35vg1c+818+0qUesWBHPgdru+XKueeCMqV/8IUlyqV7mVuI5aDSU+GDcsSE4LIu7k3RnzHs2IZcBJ1bOCjo4dqGhkuoK1vgpREjmOo6/LOhPGqQT9pQx4K+sWAFxqxTmvz6khMj0IXqa0UhCDnLsZLo+CkOqGTWy4x7ML4gumF+kP1+s3hnCi5/Ub/dHvL9TvmTDG3/8HBcczFRRPO5YZYzbLyno54fFm7j2XU5G3VE7SXVDustA+1Xst3e/6cdsQtQXjupikaMnjJER6QgEVp4t28F5f4hm2XOdBupzfgq5vr9Hlv0yXu7o/hS4INI10JSloW9qEqQAEze2aM7KYAV26a7rzVWzudS/2r25gE73yj6j49rw1PQ77OyiMaaI0/cJ+z47K5QU2/JsReONDwOsHudADifYvgLjIjsRWpfUTIhiPBHvrCHYxyCDkTbA+LHCSd6cXZd2WS0N86N+8zyC8aG0fCLcb2LOpAde0BivZGzF8GAM7dzHwXYwnpAoeBTB+ooJuDgH4lXpSEoXrCXvrTqARBuR3cwYFhYSfUCQ4mmH/hdbXD2dfOpOLoc6E1ystAjs1Xj+SRjCB0XoguLInheWtOJFiFibqYWLnay1CDdebJKfR7PzNvJH71zYAHX6mJApg/Xnug16GDuzlFgLFq7ycCsd4eR/ee5RZPPgcXKkcAl0hnMHb2PsK60Gw/sOwoQfDgnUQPJq2AKYg1DNWk7+RomXDV7OpNRm9Wti7WNKfnxa//rxnl0Nlj9mPhSQdxklzqPs8ubSMoc40hRlc5SzpG+VKaFLW8qyxdzpKM8MmF19FLXRSJ8K+EiJ3G8Y4jILY8Zxt1/0HfwgMeQ==)";
static auto S_water_replace( Item item )
{
    static auto water = Item::Named::water();
    static auto _bp = BluePrint::do_import( S_water_bp );
    auto res = _bp;

    res.icons.replace_all( water, item );
    res.train_stops_replace( water, item );
    res.locomotives_init_fuel_coal( 12 );
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
