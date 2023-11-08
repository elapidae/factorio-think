#include "decider_combinator.h"

#include "json.h"
#include "qdeb.h"

//=======================================================================================
void Decider_Combinator::first_signal( Item item )
{
    auto val = item.item_name_obj();
    auto key0 = names::control_behavior;
    auto key1 = names::decider_conditions;
    auto key2 = names::first_signal;
    Json::find_set( &obj, val, key0, key1, key2 );
}
//=======================================================================================
void Decider_Combinator::constant( int val )
{
    auto key0 = names::control_behavior;
    auto key1 = names::decider_conditions;
    auto key2 = "constant";
    Json::find_set( &obj, val, key0, key1, key2 );
}
//=======================================================================================


/* --------------------------------------
{
  "connections": {
    "1": {
      "green": [
        {
          "entity_id": 39
        }
      ]
    },
    "2": {
      "green": [
        {
          "entity_id": 42
        },
        {
          "entity_id": 47
        }
      ]
    }
  },
  "control_behavior": {
    "decider_conditions": {
      "comparator": "<",
      "constant": 42,
      "copy_count_from_input": false,
      "first_signal": {
        "name": "coal",
        "type": "item"
      },
      "output_signal": {
        "name": "train-stop",
        "type": "item"
      }
    }
  },
  "direction": 2,
  "entity_number": 41,
  "name": "decider-combinator",
  "position": {
    "x": 92,
    "y": -225.5
  }
}
 -------------------------------------- */
