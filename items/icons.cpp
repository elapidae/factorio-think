#include "icons.h"

#include "vlog.h"
#include "item.h"
#include "recipe.h"
#include "qdeb.h"

//=======================================================================================
void Icons::load_raw( QJsonArray arr )
{
    for ( auto && a: arr )
    {
        auto o = a.toObject();
        auto idx = o["index"].toDouble();
        set( idx, o["signal"].toObject() );
    }
}
//=======================================================================================
void Icons::set( int idx, Item item )
{
    if ( idx <= 0 || idx > 4 ) throw verror;

    QJsonObject o;
    o["index"] = idx;
    o["signal"] = item.item_name_obj();
    map.insert_or_assign( idx, o );
}
//=======================================================================================
template <class> class TD;
void Icons::replace_all( Item _src, Item dst )
{
    auto src = _src.item_name_obj();
    for ( const auto & [idx, val]: map )
    {
        if ( val["signal"].toObject() != src ) continue;
        set( idx, dst );
    }
}
//=======================================================================================
QJsonArray Icons::build() const
{
    QJsonArray res;
    for ( auto && it: map )
        res.append( it.second );
    return res;
}
//=======================================================================================
