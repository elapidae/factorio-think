#include "arithmetic_combinator.h"

#include "json.h"
#include "vlog.h"

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
bool Arithmetic_Combinator::replace_in_out( const Item& src, const Item& dst )
{
    auto cb = obj[names::control_behavior].toObject();
    auto ac = cb[names::arithmetic_conditions].toObject();

    auto first = ac[names::first_signal].toObject()["name"].toString();
    auto out   = ac[names::output_signal].toObject()["name"].toString();

    if ( first.isEmpty() || first != out ) throw verror << "logic replace error";

    if ( first != src.name ) return false;

    // Now first == out == src.name, let's replace.
    first_signal( dst );
    output_signal( dst );
    return true;
}
//=======================================================================================
/*
{
  "connections": {
    "1": {
      "green": [
        {
          "entity_id": 155
        }
      ]
    },
    "2": {
      "green": [
        {
          "entity_id": 213
        }
      ]
    }
  },
  "control_behavior": {
    "arithmetic_conditions": {
      "first_signal": {
        "name": "iron-ore",
        "type": "item"
      },
      "operation": "/",
      "output_signal": {
        "name": "iron-ore",
        "type": "item"
      },
      "second_constant": -12
    }
  },
  "direction": 2,
  "entity_number": 154,
  "name": "arithmetic-combinator",
  "position": {
    "x": 148,
    "y": -106.5
  }
}
*/
