#include "pr_fluids.h"

#include "items/trains.h"
#include "items/decider_combinator.h"
#include "items/constant_combinator.h"
#include "names.h"

//=======================================================================================
Blueprint_Book PR_Fluids::build()
{
    static auto water           = Item::Named::water();
    static auto crude_oil       = Item::Named::crude_oil();

    static auto heavy_oil       = Item::Named::heavy_oil();
    static auto light_oil       = Item::Named::light_oil();
    static auto petroleum_gas   = Item::Named::petroleum_gas();

    static auto sulfuric_acid   = Item::Named::sulfuric_acid();
    static auto lubricant       = Item::Named::lubricant();
    static auto steam           = Item::Named::steam();

    Blueprint_Book res;

    res.icons.set( 1, Item::Named::water() );
    res.icons.set( 2, Item::Named::lubricant() );
    res.icons.set( 3, Item::Named::virtual_signal("R") );
    res.icons.set( 4, Item::Named::virtual_signal("S") );

    //  Send
    auto gen_fn = send;
    res.add(   gen_fn(water)            );
    res.add(   gen_fn(crude_oil)        );
      res.add( gen_fn(heavy_oil)        );
      res.add( gen_fn(light_oil)        );
      res.add( gen_fn(petroleum_gas)    );
    res.add(   gen_fn(sulfuric_acid)    );
    res.add(   gen_fn(lubricant)        );
    res.add(   gen_fn(steam)            );
    res.next_line();

    // Receive
    gen_fn = receive;
    res.add(   gen_fn(water)            );
    res.add(   gen_fn(crude_oil)        );
      res.add( gen_fn(heavy_oil)        );
      res.add( gen_fn(light_oil)        );
      res.add( gen_fn(petroleum_gas)    );
    res.add(   gen_fn(sulfuric_acid)    );
    res.add(   gen_fn(lubricant)        );
    res.add(   gen_fn(steam)            );
    res.next_line();

    return res;
}
//=======================================================================================
// - set icons
// - correct burner inserteres;
// - correct decider combinator;
// - correct constant combinators;
// - correct train stop;
// - correct schedule;
BluePrint PR_Fluids::send( Item item )
{
    static auto oil = Item::Named::crude_oil();
    static auto _book = BluePrint::do_import( send_oil_template() );
    auto res = _book;

    // - set icons
    res.icons.set( 1, item );
    res.icons.set( 2, Item::Named::virtual_signal("S") );
    res.icons.set( 3, Item::Named::train_stop() );

    // - correct burner inserteres;
    res.set_burner_inserters_stack_size_1();

    // - correct decider combinator;
    res.decider_combinators_replace_first_signal( oil, item );

    // - correct constant combinators;
    res.constant_combinators_replace( oil, item );

    // - correct train stop;
    auto ref_train = res.find_unique( Item::Named::train_stop() );
    auto train = Train_Stop{ ref_train.toObject() };
    train.set_name( item, "send" );
    ref_train = train.obj;

    // - correct schedule;
    res.schedules.replace( 0, oil, item );

    // - correct fuel in locomotives
    res.locomotives_init_fuel_coal( 4 );


    return res;
}
//=======================================================================================
// - set icons
// - correct burner inserteres;
// - correct decider combinator;
// - correct constant combinators;
// - correct train stop;
BluePrint PR_Fluids::receive( Item item )
{
    static auto oil = Item::Named::crude_oil();
    static auto _book = BluePrint::do_import( receive_oil_template() );
    auto res = _book;

    // - set icons
    res.icons.set( 1, item );
    res.icons.set( 2, Item::Named::virtual_signal("R") );
    res.icons.set( 3, Item::Named::train_stop() );

    // - correct burner inserteres;
    res.set_burner_inserters_stack_size_1();

    // - correct decider combinator;
    res.decider_combinators_replace_first_signal( oil, item );

    // - correct constant combinators;
    res.constant_combinators_replace( oil, item );

    // - correct train stop;
    auto ref_train = res.find_unique( Item::Named::train_stop() );
    auto train = Train_Stop{ ref_train.toObject() };
    train.set_name( item, "receive" );
    ref_train = train.obj;

    return res;
}
//=======================================================================================


//=======================================================================================
QByteArray PR_Fluids::receive_oil_template()
{
return R"(
0eNrtmdGOmzoQht/F11BhG2KI2j5Ede6qFSLgZK2C4RgTNVrl3WtDEggxiZ3dnkpH3YtdkYTP43+Gf8bZN7ApO9oIxiVYvwGW17wF6+9v
oGU7npX6NXloKFgDJmkFPMCzSl+JjJXg6AHGC/oTrOHRM9yyZ0J26pXLXcMn/G+TO9HxxQOUSyYZHVbuLw4p76oNFQp9uTvvxJ4Wfr+0B5q6VffUXK+nOCvkgQNY+zBeKXjBBM2Hd0Md2oyJxoikwu
1e5RI1OlPxNTUyULFlpPGZGVwziYEZXinu568Z4/5J6BsygZ8u8Qafoms6MtCjC71T2RA7Uau//oaW0gAPRzjs4acs151sOgkM+JUDPoHOeOKoN4mvFVkZmLFtZRB8piaPdU6sqZEDFQbWWOKChdbYxAVr/dDF0AWLrbEuGYOhNdYpZZE11illK2usU8qILTZxSpn1Q5Y4pSxxdnUSPXZgFDxpwYTMLdhkOAg+58FkNTVJxhc8Eo
1P3aYTnAqf8ZYKqd67S7+JXT0PajaQoi7TDX3N9qwW+racibxjMlXvFRfWlolWptbjAN1TcZCvjO/0XKAnEJnpcSTQF1WTiUzqxcAXcBze50NQrWZD/WsnKOXT4YEVauv4+HI8mjQZLaOsd6yVLFdZpa0qF/pvp/4axSFz6e0DQToQD5zo6ZaVaolh2DnPT5eIeJeXNBP+tqNaqVxVg9Tz1YtpI6NJ3ckquZdVE3X0qIoWrKt8WqrPC6V
SU5fU1AbmK9hLQwZpOFWP66buelUwNG529LimqxqDtQWTMCy2OTW3WmQ76quy+2Hgonnmp0bkstnp0KhfwMFShU4c
ssrK0i8z446ja+FNpNEUG9YYkheHDxk4sFVqEk/kXAgzbeCCNhg6lme8ero8VYJmUSnrOFuevoaG8kWRqXwxsktpYrCZd7nu9blNN0bVvWTdPPRaD3QtVUuUtd6WFB1d
kE7Q4ka4lT7WmTWdSYhmEodLto1H2y5ozlSv9FXIG8b7kG9nh2DR9ZBZ1RN1VLW9I+u27FS04wlEdAX16+FQPMqKAvUzk/azums41LgmqzmkfT9It6Ku0qHnr7dZ2VKnxtg/Wh5Ayx+Y5wQnSzmx6UBx7NiBcPREg56u4tigcfybGjQee9a5Jh7
U7MNWc1O102CtR65NmeU/hqIawp98H+N9CAd/ECf8IE7kxBnKxMSBw8Nj64No6cEhz303Yjn249h+7E/g/2rsx9GS5InJWO+cOYnV89dSXqSyTnvmyY69YYVUr9DQwl6Tf7QULZUDrU1LVjE5NN8T8/SaS+twUu+mO/fOqFIziAC+943vy6XfvSh9KNtTUxWGgeN3twRdSw5N0GcPzJHdt4ohejQxB9dMEwM7D3vRHxz2vr5v2Auj5WFvyf/
C8En/s81i9Hznjf523j/XeXV9vb/vLh4iQteJDH9wXdw/N8w33bvv7SaI4ybQf1Tc3xYKW+1COURvTuvJPxw9oEaAdogihiFJECExjrE6PR5/AXuUgHQ=
)";}
//=======================================================================================
QByteArray PR_Fluids::send_oil_template()
{
return R"(
0eNrtmduSozYQht+FazPF0YBrN1d5g+Rua4rCIHtUKxAR0kycKb97Wsg2GAtbYp1sVSo34zGHT92t7r8b/OlsiUAtww13Np8OLmnTOZtvn06H901B5DF+aJGzcd4x4wKOrJymqOUBdYX7q3NcObip0J/Oxj++rhzUcMwxUpj+yyFvRL1FDC643F0K9o4qlxVYIlvawT20kesBZx2snIOzcQMvBXiFGSrV2ei4umEGg0UccPs3PkeNz9T4mhprqKGhpemZGVwzEw0zujAFxIvtGYVPd4sIvwUn0cvFXPgX4Kd9wE0ruKOhxxb0zLelry90GQi3fCtw456S5Nb4ET54mUQ70NCThZEJx7ZTwWeMTxeGxhCf2eaKdx2RtYbpexcooSWtKcfvSBOM9ZnpA5MyDJhCnfdeEnAEc1R38uKSynKWKShKggrm7gQicjd0i/umNZWE4/Uf7LJvXKpJbIMNjbGJDTYyxmY22KFOd0Tgyv0o9nDtDTQN7+6sjrw2NTj1bQxOjLFWyZAaY62SITOqm8y7E91gad0EnrFPNpkYGJdjapOJgXE5Zjb5EhiXY2aTL0Fk2+f9LHnck4N4WWPzs2za2HQyHgw1uRWsQczFTYcYh3N3GpsGDt7DbMYZJfkWvRXvmLI+OzErBeY5nKsurB1mHc+NJzj0jtiBv+FmL0c5OQHyQo6DnvxStwUruFzM+eoc1flGGdWXhy//7BlCzXjewxW4nh1f5Q0U8AxXKAds+R3M+gvJSVETq2VTgJ+lRhNMMAjOnT1I7u2BjjrWmz3uOC4hh1AHyYn+EPD5aBVlvHlU1yqqJ3q+wwSWUMP2eQq/WHQlWXIRIfcVpnTdwDtoV40qLGoXEbCIgT8tJbrRI5uGytiJMFBONAjKeEtFb3+41po1eNOKutVInjcyQyfK4VjmKCv2yIX8/q4hBdNdGUuSjXveyIz+QCT91dk20sq6IMQlhdbH+DrUOlJk6uWIlVhv28Sv9Zxfg6q2uNUkTxo99mhtmZDpenlCRlPPoKzP2iq/+7qE9bQJmxjITJpaykyYLpCZ8SqWMhP5/5TMDHpZoRLaAnOhyWxx0zeZ2TlNE6ZA3xFP1KEjdndaYj+BDw2xZKJCLoWh4qoRwgObN22GX+Au9UR4S5Wz4wCVwwpMFJy2itoe8j5C+Y7ROlftarMrSIes2mtfeysnmN9Cb6Y4I89MdDJN9vzQAHI/LnfGjpUjOgRLECpTkDOBZiLFUHUThkC+lNKHcFLkU3mL0rkI+uZTXeb/p6a6MLWc6qKh/Z6NeFDxD7vwTbzG6mQcoC0Bw1VslF5dXmP2efAETvgkTvQkTmzFKQ9Fo8X4vbIb19+sDIWL3sqZjvtRpFOa2WdQOTyapFqHmirnNO+ZJ91eqRVyuUKLKvMa/V3Gt0Nc0bqc4BpzJXAn5umYjZZK5PldhvOt73BfL43tVdoP99VFAwZN1tWWb2z3yt7Pous4aqHrhU96idkL2Sh5NH5610wdI7XukslP7JK//FiXjL3ZLjlfwNnCAjbcxdhb3jmS/zvHz+scB0QI/XhG75gbwGLfMjXCJ6fG/QeHqdP9yHTrhO1kFPxL+f3bTG6DFyASHTx3VoKcfuAdXrLL77638rPRNWrdh93ooxhrowIrdUP5WSZkQM7BFwQC3T9d3mFDaJB692+JR3XLD5L/Kt3t5Xgz+pl85cDo26mgp36UZEGSpGEawgPZ8W8cIGnO
)";}
//=======================================================================================

