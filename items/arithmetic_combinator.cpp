#include "arithmetic_combinator.h"

#include "json.h"

//=======================================================================================
void Arithmetic_Combinator::first_signal( const Item& item )
{
    auto val = item.item_name_obj();
    auto key0 = names::control_behavior;
    auto key1 = names::arithmetic_conditions;
    auto key2 = names::first_signal;
    Json::find_set( &obj, val, key0, key1, key2 );
}
//=======================================================================================
void Arithmetic_Combinator::output_signal( const Item& item )
{
    auto cb = obj[names::control_behavior].toObject();
    auto ac = cb[names::arithmetic_conditions].toObject();
    ac[names::output_signal] = item.item_name_obj();
    cb[names::arithmetic_conditions] = ac;
    obj[names::control_behavior] = cb;
}
//=======================================================================================
