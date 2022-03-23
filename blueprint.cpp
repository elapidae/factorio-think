#include "blueprint.h"

#include "vlog.h"
#include <QProcess>
#include <QPoint>
#include <QSet>


//=======================================================================================
QJsonObject BluePrint::extract(QByteArray code)
{
    QByteArray arr( code );
    if ( arr.at(0) != '0' ) throw verror;
    arr.remove(0,1);

    if ( !arr.fromBase64Encoding(arr) ) throw verror;

    QProcess proc;
    QObject::connect( &proc, &QProcess::stateChanged,
    [](QProcess::ProcessState)
    {
        //vdeb << state;
    });

    QObject::connect( &proc, &QProcess::errorOccurred,
    [&](QProcess::ProcessError error)
    {
        vdeb << "err" << error;
        throw verror;
    });
    QByteArray doc;
    QObject::connect( &proc, &QProcess::readyReadStandardOutput,
    [&]
    {
        doc += proc.readAllStandardOutput();
    });
    QString cmd = "echo \"" + arr + "\"|base64 -d|zlib-flate -uncompress";
    //vdeb << cmd;
    proc.start( "bash", QStringList{"-c",cmd} );
    proc.waitForFinished();
    //vdeb << doc;

    auto json = QJsonDocument::fromJson(doc);
    return json.object();
}
//=======================================================================================
//  Add '0' to begin.
QByteArray BluePrint::pack(QJsonObject obj)
{
    QProcess proc;
    QObject::connect( &proc, &QProcess::stateChanged,
    [](QProcess::ProcessState)
    {
        //vdeb << state;
    });

    QObject::connect( &proc, &QProcess::errorOccurred,
    [&](QProcess::ProcessError error)
    {
        vdeb << "err" << error;
        throw verror;
    });
    QByteArray res = "0";
    QObject::connect( &proc, &QProcess::readyReadStandardOutput,
    [&]
    {
        res += proc.readAllStandardOutput();
    });

    auto arr = QJsonDocument(obj).toJson(QJsonDocument::Compact);

    QString cmd = "echo '" + arr + "'|zlib-flate -compress=9|base64 --wrap=0";

    proc.start( "bash", QStringList{"-c",cmd} );
    proc.waitForFinished();

    return res;
}
//=======================================================================================
static constexpr auto entities_n = "entities";
static constexpr auto tiles_n = "tiles";

/*
    {
        "name": "landfill",
        "position": {
            "x": 338,
            "y": 378
        }
    },
*/
std::vector<QPoint> square_of_coord(const QPoint& pos, int w, int h)
{
    std::vector<QPoint> res;
    auto stop_x = pos.x() + w/2; if (w % 2 == 0) --stop_x;
    auto stop_y = pos.y() + h/2; if (h % 2 == 0) --stop_y;

    for (int x = pos.x() - w/2; x <= stop_x; ++x)
    {
        for (int y = pos.y() - h/2; y <= stop_y; ++y)
        {
            res.push_back( {x,y} );
        }
    }
    return res;
}

static constexpr auto roboport_n = "roboport";
static constexpr auto position_n = "position";
static constexpr auto name_n = "name";
static constexpr auto landfill_n = "landfill";
static constexpr auto curved_rail_n = "curved-rail";
static constexpr auto straight_rail_n = "straight-rail";
static constexpr auto logistic_chest_storage_n = "logistic-chest-storage";
static constexpr auto rail_chain_signal_n = "rail-chain-signal";
static constexpr auto medium_electric_pole_n = "medium-electric-pole";
static constexpr auto small_lamp_n = "small-lamp";
static constexpr auto radar_n = "radar";
static constexpr auto big_electric_pole_n = "big-electric-pole";
static constexpr auto laser_turret_n = "laser-turret";
//static constexpr auto _n = "";
//static constexpr auto _n = "";
//static constexpr auto _n = "";

/*
        "entity_number": 1,
        "name": "roboport",
        "position": {
            "x": 338,
            "y": 370
        }
*/
auto entities_1_1 = []
{
    QSet<QString> res;
    res.insert(logistic_chest_storage_n);
    res.insert(rail_chain_signal_n);
    res.insert(medium_electric_pole_n);
    res.insert(small_lamp_n);
    return res;
}();

auto entities_2_2 = []
{
    QSet<QString> res;
    res.insert(laser_turret_n);
    res.insert(big_electric_pole_n);
    return res;
}();

auto entities_3_3 = []
{
    QSet<QString> res;
    res.insert(radar_n);
    return res;
}();

//=======================================================================================
std::vector<QPoint> square_of(const QString& name, const QPoint& pos)
{
    if (entities_1_1.contains(name))        return square_of_coord(pos, 1, 1);
    if (entities_2_2.contains(name))        return square_of_coord(pos, 2, 2);
    if (entities_3_3.contains(name))        return square_of_coord(pos, 3, 3);

    if (name == roboport_n)                 return square_of_coord(pos, 4, 4);

    if (name == straight_rail_n) { vwarning << name; return {}; }
    if (name == curved_rail_n)   { vwarning << name; return {}; }

    throw verror << "unknown entity: " << name;
}
//=======================================================================================
void process_entity(QJsonArray *tiles, const QJsonObject& ent)
{
    auto pos_o = ent[position_n].toObject();
    QPoint pos( pos_o["x"].toDouble(), pos_o["y"].toDouble() );
    auto name = ent[name_n].toString();

    auto list = square_of(name, pos);
    for(auto lf: list)
    {
        QJsonObject p;
        p["x"] = lf.x();
        p["y"] = lf.y();

        QJsonObject np;
        np[name_n] = landfill_n;
        np[position_n] = p;

        tiles->append(np);
    }
}
//=======================================================================================
QJsonObject BluePrint::correct_landfill(QJsonObject src)
{
    //if (!src.keys().contains(tiles_n)) throw verror;
    if (!src.keys().contains(entities_n)) throw verror;
    if (!src[entities_n].isArray()) throw verror;

    auto entities = src[entities_n].toArray();

    QJsonArray landfills;
    for (auto ent: entities)
    {
        process_entity(&landfills, ent.toObject());
    }
    src[tiles_n] = landfills;
    return src;
}
//=======================================================================================
