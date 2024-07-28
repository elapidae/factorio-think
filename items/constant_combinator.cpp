#include "constant_combinator.h"

#include "vlog.h"
#include "names.h"
#include "json.h"
#include "control_behavior.h"

//=======================================================================================
QJsonArray Constant_Combinator::filters() const
{
    if ( !obj.contains(names::control_behavior) )
        return {};

    auto cb = Json::get_obj( obj, names::control_behavior );
    return cb[ names::filters ].toArray();
}
//=======================================================================================
void Constant_Combinator::filters( QJsonArray arr )
{
    auto cb = obj[names::control_behavior].toObject();
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
Item Constant_Combinator::get_item( int index )
{
    auto cb = obj[names::control_behavior].toObject();
    auto f = cb[names::filters].toArray();
    auto field = f.at(index).toObject();
    auto signal = field["signal"].toObject();

    return Item::get( signal["name"].toString() );
}
//=======================================================================================
void Constant_Combinator::normalize_as_info()
{
    remove_direction();

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
void Constant_Combinator::remove_direction()
{
    obj.remove( names::direction );
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
    for ( auto && ing : recipe.ingredients )
    {
        Item item;
        if ( ing.name == "lubricant" )
        {
            item.name = "lubricant";
            item.type = "fluid";
        }
        else
        {
            item = Item::get( ing.name );
        }
        set_behavior( idx++, item, ing.amount );
    }
}
//=======================================================================================
bool Constant_Combinator::contains( Item item ) const
{
    auto fs = filters();
    for ( auto f: fs )
    {
        auto sig = f.toObject()["signal"].toObject();
        if ( sig["name"] == item.name )
            return true;
    }
    return false;
}
//=======================================================================================


//=======================================================================================
Constant_CombinatorRef::Constant_CombinatorRef(QJsonValueRef ref)
    : ref( ref )
{}
//=======================================================================================
Constant_CombinatorRef
Constant_CombinatorRef::find( QList<QJsonValueRef> where, Item what )
{
    for ( auto ref: where )
    {
        Constant_CombinatorRef cc( ref );
        if ( cc.contains(what) ) return cc;
    }
    throw verror << "not found";
}
//=======================================================================================
void Constant_CombinatorRef::clear_behavior()
{
    Constant_Combinator cc{ ref.toObject() };
    cc.clear_behavior();
    ref = cc.obj;
}
//=======================================================================================
void Constant_CombinatorRef::replace_all( Item src, Item dst )
{
    Constant_Combinator cc{ ref.toObject() };
    cc.replace_all( src, dst );
    ref = cc.obj;
}
//=======================================================================================
void Constant_CombinatorRef::save_recipe( Recipe recipe )
{
    Constant_Combinator cc{ ref.toObject() };
    cc.save_recipe( recipe );
    ref = cc.obj;
}
//=======================================================================================
bool Constant_CombinatorRef::contains( Item item ) const
{
    Constant_Combinator cc{ ref.toObject() };
    return cc.contains( item );
}
//=======================================================================================
void Constant_CombinatorRef::set_behavior( int index, Item item, int count )
{
    Constant_Combinator cc{ ref.toObject() };
    cc.set_behavior( index, item, count );
    ref = cc.obj;
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

