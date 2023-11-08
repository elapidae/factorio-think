#include "constant_combinator.h"

#include "vlog.h"
#include "names.h"
#include "json.h"

//=======================================================================================
QJsonArray Constant_Combinator::filters() const
{
    auto cb = Json::get_obj( obj, names::control_behavior );
    return cb[ names::filters ].toArray();
}
//=======================================================================================
void Constant_Combinator::filters( QJsonArray arr )
{
    auto cb = Json::get_obj( obj, names::control_behavior );
    cb[ names::filters ] = arr;
    obj[ names::control_behavior ] = cb;
}
//=======================================================================================
void Constant_Combinator::clear_behavior()
{
    filters( QJsonArray{} );
}
//=======================================================================================
void Constant_Combinator::set_behavior( int index, Item item, int count )
{
    if ( index <=0 ) throw verror;

    auto f = filters();

    QJsonObject dst;
    dst["count"] = count;
    dst["index"] = index;
    dst["signal"] = item.item_name_obj();

    while ( f.size() < index ) f.append( {} );
    f[index-1] = dst;

    filters( f );
}
//=======================================================================================
void Constant_Combinator::normalize_as_info()
{
    obj.remove( names::direction );

    auto ff = filters();

    int idx = 1;
    for ( auto ref: ff )
    {
        auto o = ref.toObject();
        o["count"] = 0;
        o["index"] = idx++;
        ref = o;
    }

    filters( ff );
}
//=======================================================================================
void Constant_Combinator::replace_all( Item _src, Item _dst )
{
    auto ff = filters();

    auto src = _src.item_name_obj();
    auto dst = _dst.item_name_obj();
    for ( auto ref: ff )
    {
        auto o = ref.toObject();
        auto s = o["signal"].toObject();
        if ( s != src ) continue;
        o["signal"] = dst;
        ref = o;
    }
    filters( ff );
}
//=======================================================================================
void Constant_Combinator::save_recipe( Recipe recipe )
{
    clear_behavior();

    int idx = 1;
    for ( auto && ing : recipe.ingredients ) {
        auto item = Item::get( ing.name );
        set_behavior( idx++, item, ing.amount );
    }
}
//=======================================================================================


/* // -------------------
{
  "connections": {
    "1": {
      "red": [
        {
          "entity_id": 42
        }
      ]
    }
  },
  "control_behavior": {
    "filters": [
      {
        "count": 1,
        "index": 2,
        "signal": {
          "name": "signal-black",
          "type": "virtual"
        }
      },
      {
        "count": 1,
        "index": 3,
        "signal": {
          "name": "signal-black",
          "type": "virtual"
        }
      },
      {
        "count": 1,
        "index": 4,
        "signal": {
          "name": "signal-black",
          "type": "virtual"
        }
      },
      {
        "count": 1,
        "index": 5,
        "signal": {
          "name": "signal-black",
          "type": "virtual"
        }
      },
      {
        "count": 1,
        "index": 11,
        "signal": {
          "name": "signal-green",
          "type": "virtual"
        }
      }
    ]
  },
  "direction": 2,
  "entity_number": 45,
  "name": "constant-combinator",
  "position": {
    "x": 92.5,
    "y": -224.5
  }
}
*/ // -------------------
