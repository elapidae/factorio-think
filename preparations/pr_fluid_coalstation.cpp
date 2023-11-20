#include "pr_fluid_coalstation.h"

#include "blueprint_io.h"

//=======================================================================================
Blueprint_Book PR_Fluid_CoalStation::rs_pairs()
{
    Blueprint_Book res;

    res.add( rs_pair(Item::Named::heavy_oil()) );
    res.add( rs_pair(Item::Named::light_oil()) );
    res.add( rs_pair(Item::Named::petroleum_gas()) );

    return res;
}
//=======================================================================================
BluePrint PR_Fluid_CoalStation::rs_pair( Item fluid )
{
    static auto tmpl = BluePrint::do_import( rs_pair_heavy_oil() );
    auto res = tmpl;
    auto src = Item::Named::heavy_oil();

    res.train_stops_replace( src, fluid );
    res.constant_combinators_replace( src, fluid );
    res.decider_combinators_replace_first_signal( src, fluid );
    res.locomotives_init_fuel_coal( 4 );
    res.icons.replace_all( src, fluid );

    return res;
}
//=======================================================================================
QByteArray PR_Fluid_CoalStation::rs_pair_heavy_oil()
{
return R"(
0eNrtWtmOozgU/Rc/Qwm8AImm5yO6R5qHVgkR4qSsZhuW1ESt/PvYkASSXAdMop5WqeqhqrL4cO695y42/ESrpOFFKbIaLX8iEedZhZbff6JKbLMoUe/V+4KjJdokjVgjC2VRql6+8Wi3t3ORoIOFRLbm/6Kle7CAhTtR1o1857y0+4b992AlNlr5dbCSGK38NlhJD68W4lktasE7m9sX+zBr0hUvpTn96rqMxPattuUfBVrklVyVZ+qKEsnGnm+hvfyHuOygCF0h4TOSAsrsqs4LEIb1MBaSsajLPAlX/C3aibxUX6t4tg7rPGxx0HITJRW3OtRQoRZ8HU72xl/KGxWvO7QqTEQqpAzqsjlhHt+7hRQ1TxFk1aEjnvFYWVapJa76tS05z4ZelmJautLFsSjjRl5CvcaHV7W+qqPOLeh7q7ovZ7G9vkclf8ubitslj7nYcQS4m5yJKTnXUVbbcZ6uRBbV0ouQ38nL2fP0Ref7jUhqXmrS467K47xR+eXOzJSvIEbnrBvj6SPGs3nG36sNgO0gb2bM2/kteHuP8H6y2L6ZCMU/r05yyTivVTYBfNnixFZWaZSXQuIc89MBYIPpVbNHBqvmYmLVZP6HqJp3qp7iL9elUSYJXV3XBTznOnNaF4GC4PZdcM1jseblmLxZL2+siccRKZSfrcW5T2xEWQFOu5+kXcpJkTvyR72RFlHZcluiP+SqvKmLxigUCqTYh20ahZsyT0ORSYijbIz6G17I1LMQ1n9h4PG2IaoFYBiwcZmhgzg8t8yskij+oSk11lNwyJNw6JNwmBFOF2qwh7itICABlXx9Mx5p1UBMkxJ/JuX0pMQ6tz80W30m4S9NQpVPj6cgdnVaMJ9X3U8t/E9aiPfRM+qxvjA8tAn4FMMvFcOeJ0n+/gw5EJ0c/Dl7IHj8DuZM8i4I1e+nqjRKEjuJ0mJscnS12jyd25zHhTvTwv2+fpoWrieFL+rjpuLyEkmuskBtsQymJ6wO+CaeO1nTqj52pvpwsAuSqQ5iuVOxyO8Rjz8fjAfVx0M36GI81Ufux9As0/uIjGhWV40wmepD52PozNP6UNvAMZ1TscEyi9ngXG0rqlrEdvzGKwnI/2nkXw4OBMy7LBgWOn49HA4Bpz51vkTWxAmPSnvTcEX21NFUG7tl5k0UAvMvhQBh9S1OZBUvdVb511atRdnF8FLBZ9w5/c5ZgBT7fpfytWhSmyfy0qWMR5EnfKRqO8EpA+bdynCvT3bI/c+J0937yLi0eZU3bcCpD8WRDE/38jLaclsm0o+R1uH4N/432zRf8Q00qURcc7c7126f4gU8I2VhpRAyR3Q+CNUXkkIUoyLz4OwifQ1pD1rs92grEe5axm4O518YBO3NcRtsqz/HbbDBwXRJ99OpQ81ylDhXIqa+TsSLOV4CTaNzzuIdcDNA+9QqmvT+HWQHTym3FI/LtT86dAgsV0rGUQaFCGtQ6Lh17pDJuHVsThRh13tzoggOCNR/qC+5hpoPgL4iW6Ms0zSA6ioNHqrf7tT6TReG9x/xIphW4pgzJ+xgrNiMZ0DwAmwyDBtvHaXFcKowYm6hjhY1Hgr1tJjhUCg5Tclj5j04Up+u8/SRmvlz9AF2UxbMiSkMtZjDCgyp58xhBUP1Lo6bcsfXek7BCci5FAeU7V6fVwpPCqPdZXZbURC8V4Wmn3lkMlNPw5RCsNSQKbtkOn4BNpm3Y+Jhz5C3M+5hfypTFph4ODBjOqxE0zy8mMrbp0fggI4XON8gy3z3BOxfAhMI2DVW8iS+BnsvlUwgX0hqPjFW8DVfH4KlT+AL+tdkwmQmjvAmJwjWOuLVQpXsk+smOT7g2g9a6rVv0cXgK91dptGHkN6j4eFfh9sd3/HweOzX3vI6PSjQJAnqeucd7NPDnMbwPC3qvcJ/Vda2543LwSPNFtrJPt/pOHCpv8C+H5CAEO9w+A9o9toA

)"; }
//=======================================================================================
