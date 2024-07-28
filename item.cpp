#include "item.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include "vlog.h"

//=======================================================================================
static auto _load = []
{
    auto from = vsteady_time_point::now();
    QMap<QString, QJsonObject> res;

    auto path = "/home/el/red/factorio/script-output/items.json";
    QFile f(path);
    if ( !f.open(QIODevice::ReadOnly) ) throw verror;
    auto arr = QJsonDocument::fromJson( f.readAll() ).array();

    for ( auto && it: arr )
    {
        auto o = it.toObject();
        res.insert(o["name"].toString(), o);
    }
    auto to = vsteady_time_point::now();
    vdeb << "items.json loaded in " << (to-from).milliseconds();
    return res;
};
static auto & load()
{
    static auto res = _load();
    return res;
}
Item Item::get( QString name )
{
    if ( name.startsWith("signal-") )
    {
        name.replace( "signal-", "" );
        return Item::virtual_signal( name );
    }
    if ( !load().keys().contains(name) )
        throw verror << name;

    auto o = load()[name];
    return Item( o );
}
//=======================================================================================
QStringList Item::keys()
{
    return load().keys();
}
//=======================================================================================


//=======================================================================================
Item::Item( int s, QString t, QString n )
    : stack_size( s )
    , type( t )
    , name( n )
{}
//=======================================================================================
Item Item::virtual_signal( QString name )
{
    return { -1, "virtual", "signal-" + name };
}
//=======================================================================================
int Item::optimum_station_count() const
{
    if ( type == "fluid" ) return 20000;
    if ( stack_size <= 0 ) throw verror;

    auto cells_in_chest = 16;
    auto chests_count = 12;
    return stack_size * chests_count * cells_in_chest / 2;
}
//=======================================================================================
Item::Item( const QJsonObject& o )
{
    item_type = o["item-type"].toString();
    type = o["type"].toString();
    name = o["name"].toString();
    stack_size = o["stack_size"].toDouble();
}
//=======================================================================================
Item Item::item( int stack_size, QString name )
{
    return { stack_size, "item", name };
}
//=======================================================================================
Item Item::fluid( QString name )
{
    return { 25000, "fluid", name };
}
//=======================================================================================
