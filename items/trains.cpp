#include "trains.h"

#include "qdeb.h"

//=======================================================================================
void Train_Stop::set_name( Item item, QString suffix )
{
    obj["station"] = item.label() + suffix;
}
//=======================================================================================
void Train_Stop::replace( Item src, Item dst )
{
    auto station = obj["station"].toString();
    station.replace( src.name, dst.name );
    obj["station"] = station;
}
//=======================================================================================


//=======================================================================================
void Schedules::replace( int pos, Item _from, Item _to )
{
    if ( pos >= arr.size() )
        throw verror << "Schedule not exists";

    auto from = _from.label();
    auto to = _to.label();

    auto obj = arr.at( pos ).toObject();
    auto sch = obj["schedule"].toArray();

    for ( auto ref: sch )
    {
        auto o = ref.toObject();
        auto station = o["station"].toString();
        station.replace( from, to );
        o["station"] = station;
        ref = o;
    }
    obj["schedule"] = sch;
    arr[pos] = obj;
}
//=======================================================================================


//=======================================================================================
void Locomotive::clear_fuel()
{
    obj.remove( "items" );
}
//=======================================================================================
void Locomotive::coal( int count )
{
    auto i = obj["items"].toObject();
    i["coal"] = count;
    obj["items"] = i;
}
//=======================================================================================
void Locomotive::nuclear_fuel( int count )
{
    auto i = obj["items"].toObject();
    i["nuclear-fuel"] = count;
    obj["items"] = i;
}
//=======================================================================================
/* -----------------------------------------
 * Locomotive
{
  "entity_number": 82,
  "items": {
    "coal": 50,
    "nuclear-fuel": 2
  },
  "name": "locomotive",
  "orientation": 0.75,
  "position": {
    "x": 120,
    "y": -201
  }
}
----------------------------------------- */

/* -----------------------------------------
 * Schedules
[
  {
    "locomotives": [
      82,
      91
    ],
    "schedule": [
      {
        "station": "[item=coal]send",
        "wait_conditions": [
          {
            "compare_type": "or",
            "type": "full"
          }
        ]
      },
      {
        "station": "[item=coal]receive",
        "wait_conditions": [
          {
            "compare_type": "or",
            "type": "empty"
          }
        ]
      }
    ]
  }
]
----------------------------------------- */
//=======================================================================================
/* -----------------------------------------
 * Train stop
{
  "connections": {
    "1": {
      "green": [
        {
          "circuit_id": 2,
          "entity_id": 41
        }
      ]
    }
  },
  "control_behavior": {
    "send_to_train": false,
    "set_trains_limit": true,
    "train_stopped_signal": {
      "name": "signal-T",
      "type": "virtual"
    },
    "trains_limit_signal": {
      "name": "train-stop",
      "type": "item"
    }
  },
  "direction": 2,
  "entity_number": 47,
  "name": "train-stop",
  "position": {
    "x": 95,
    "y": -225
  },
  "station": "[item=coal]warehouse"
}
-------------------------------------- */


