#include "bprint_landfill.h"

#include <QProcess>
#include <QPoint>
#include <QSet>
#include <cmath>
#include <QFile>
#include "qdeb.h"

//=======================================================================================
static auto constexpr blueprint_n = "blueprint";
QJsonObject BPrint_Landfill::correct_blueprint_landfill( QJsonObject src )
{
    auto _bp_o = src[blueprint_n];
    if ( !_bp_o.isObject() )
        throw verror;

    auto o = _bp_o.toObject();

    auto corrected = BPrint_Landfill::correct_landfill(o);

    QJsonObject res_obj;
    res_obj[blueprint_n] = corrected;
    return res_obj;
}
//=======================================================================================
static constexpr auto entities_n = "entities";
static constexpr auto tiles_n = "tiles";

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
static constexpr auto radar_n = "radar";
static constexpr auto big_electric_pole_n = "big-electric-pole";
static constexpr auto laser_turret_n = "laser-turret";
static constexpr auto assembling_machine_2_n = "assembling-machine-2";
static constexpr auto flamethrower_turret_n = "flamethrower-turret";
static constexpr auto heat_exchanger_n = "heat-exchanger";
//static constexpr auto _n = "";
//static constexpr auto _n = "";
//static constexpr auto _n = "";
//static constexpr auto _n = "";
//static constexpr auto _n = "";

auto entities_0_0_no_landfill = []
{
    QSet<QString> res;
    res.insert("stone-wall");
    res.insert("gate");
    res.insert("locomotive");
    res.insert("fluid-wagon");
    res.insert("cargo-wagon");
    res.insert("");
    res.insert("");
    res.insert("");
    return res;
}();

auto entities_1_1 = []
{
    QSet<QString> res;
    res.insert(logistic_chest_storage_n);
    res.insert(rail_chain_signal_n);
    res.insert(medium_electric_pole_n);
    res.insert("small-lamp");
    res.insert("rail-signal");
    res.insert("pipe-to-ground");
    res.insert("pipe");
    res.insert("logistic-chest-active-provider");
    res.insert("fast-inserter");
    res.insert("logistic-chest-requester");
    res.insert("heat-pipe");
    res.insert("constant-combinator");
    res.insert("stack-inserter");
    res.insert("logistic-chest-passive-provider");
    res.insert("underground-belt");
    res.insert("inserter");
    res.insert("programmable-speaker");
    res.insert("transport-belt");
    res.insert("burner-inserter");
    res.insert("wooden-chest");
    res.insert("long-handed-inserter");
    res.insert("fast-transport-belt");
    res.insert("fast-underground-belt");
    res.insert("small-electric-pole");
    res.insert("steel-chest");
    res.insert("express-transport-belt");
    res.insert("express-underground-belt");
    res.insert("");
    res.insert("");
    res.insert("");
    return res;
}();

auto entities_2_2 = []
{
    QSet<QString> res;
    res.insert(laser_turret_n);
    res.insert(big_electric_pole_n);
    res.insert("train-stop");
    res.insert("substation");
    res.insert("steel-furnace");
    res.insert("accumulator");
    res.insert("power-switch");
    res.insert("");
    res.insert("");
    return res;
}();

auto entities_3_3 = []
{
    QSet<QString> res;
    res.insert(radar_n);
    res.insert(assembling_machine_2_n);
    res.insert("storage-tank");
    res.insert("assembling-machine-1");
    res.insert("assembling-machine-2");
    res.insert("assembling-machine-3");
    res.insert("artillery-turret");
    res.insert("electric-furnace");
    res.insert("solar-panel");
    res.insert("lab");
    res.insert("chemical-plant");
    res.insert("beacon");
    res.insert("");
    return res;
}();

//=======================================================================================
std::vector<QPoint> square_of(const QString& name, const QPoint& pos)
{
    if (entities_0_0_no_landfill.contains(name)) return {};

    if (entities_1_1.contains(name))        return square_of_coord(pos, 1, 1);
    if (entities_2_2.contains(name))        return square_of_coord(pos, 2, 2);
    if (entities_3_3.contains(name))        return square_of_coord(pos, 3, 3);

    if (name == roboport_n)                 return square_of_coord(pos, 4, 4);

    if (name == "nuclear-reactor")          return square_of_coord(pos, 5, 5);
    if (name == "oil-refinery")             return square_of_coord(pos, 5, 5);


    if (name == straight_rail_n) { vwarning << name; return {}; }
    if (name == curved_rail_n)   { vwarning << name; return {}; }

    throw verror << "unknown entity: " << name;
}
//=======================================================================================
//  Если направление диагональное, то direction = 1,3,5,7, результат -- крестик;
//  положение крестика относительно координат описывается смещением.
//
//  Если нет, то координата в правом верхнем углу.
std::vector<QPoint> land_of_straight_rail(const QJsonObject& obj, QPoint pos)
{
    auto x = pos.x();
    auto y = pos.y();

    //  Координаты всегда нечетные.
    if (x % 2 == 0 || y % 2 == 0) throw verror("not odd xy: ", x, ",", y);

    //  четное направление
    auto dir = obj["direction"].toInt(0);
    if (dir % 2 == 0)
        return {
            {x,   y},
            {x,   y-1},
            {x-1, y},
            {x-1, y-1}
        };

    //  нечетные направления, результат крестик, координаты сводятся в центр.
    if (dir == 5 || dir == 7) --x;
    if (dir == 1 || dir == 7) --y;

    return {
        {x,   y},
        {x,   y-1},
        {x,   y+1},
        {x-1, y},
        {x+1, y}
    };
}
//=======================================================================================
std::vector<QPoint> transpose(std::vector<QPoint> points)
{
    for (auto& p: points)
    {
        p = {-p.y(), p.x()};
    }
    return points;
}
//=======================================================================================
std::vector<QPoint> mirror(std::vector<QPoint> points)
{
    for (auto& p: points)
    {
        p = {p.x(), -p.y()};
    }
    return points;
}
//=======================================================================================
std::vector<QPoint> land_of_curved_rail(const QJsonObject& obj, QPoint pos)
{
    static std::vector<QPoint> even_offsets =
    {
        {-3,-3},{-3,-2},
        {-2,-4},{-2,-3},{-2,-2},{-2,-1},
        {-1,-3},{-1,-2},{-1,-1},{-1, 0},
        { 0,-2},{ 0,-1},{ 0, 0},{ 0,+1},{ 0,+2},{ 0,+3},
        {+1, 0},{+1,+1},{+1,+2},{+1,+3}
    };

    auto x = pos.x();
    auto y = pos.y();
    //  Координаты всегда четные.
    if (x % 2 != 0 || y % 2 != 0) throw verror("not even xy: ", x, ",", y);

    auto offsets = even_offsets;
    auto dir = obj["direction"].toInt(0);

    if (dir % 2)
    {
        if (dir == 1) {--x;}
        if (dir == 3) {--y;}
        if (dir == 5) {++x;}
        if (dir == 7) {++y;}

        offsets = mirror(offsets);
        offsets = transpose(offsets);
        offsets = transpose(offsets);
        --dir;
    }

    if (dir == 2 || dir == 4) --x;
    if (dir == 4 || dir == 6) --y;

    //  для четных поворотов транспонируем
    if (dir % 2 == 0)
    {
        while (dir)
        {
            dir -= 2;
            offsets = transpose(offsets);
        }
    }

    std::vector<QPoint> res;
    for (auto &o: offsets)
    {
        res.push_back( {x+o.x(), y+o.y()} );
    }

    return res;
}
//=======================================================================================
std::vector<QPoint> land_of_flamethrower_turret(const QJsonObject& obj, QPoint pos)
{
    static const std::vector<QPoint> _offsets =
    {
        {-1,-1}, { 0,-1},
        {-1, 0}, { 0, 0},
        {-1,+1}, { 0,+1}
    };
    auto ofs = _offsets;

    auto dir = obj["direction"].toInt(0);
    if (dir == 2 || dir == 6)
        ofs = transpose(ofs);

    auto x = pos.x();
    auto y = pos.y();

    std::vector<QPoint> res;
    for (auto &o: ofs)
    {
        res.push_back( {x+o.x(), y+o.y()} );
    }

    return res;
}
//=======================================================================================
std::vector<QPoint> land_of_heat_exchanger(const QJsonObject& obj, QPoint pos)
{
    auto dir = obj["direction"].toInt(0);
    if (dir == 2 || dir == 6)
        return square_of_coord(pos, 2, 3);

    return square_of_coord(pos, 3, 2);
}
//=======================================================================================
std::vector<QPoint> land_of_direction(const QJsonObject& obj, QPoint pos, int w, int h)
{
    auto dir = obj["direction"].toInt(0);
    if (dir == 2 || dir == 6)
        return square_of_coord(pos, w, h);

    return square_of_coord(pos, h, w);
}
//=======================================================================================
std::vector<QPoint> offshore_pump_land(const QJsonObject& obj, QPoint pos)
{
    std::vector<QPoint> res;
    res.push_back(pos);

    auto dir = obj["direction"].toInt(0);

    auto dx = 0;
    auto dy = 0;

    if (dir == 0) dy = +1;
    if (dir == 2) dx = -1;
    if (dir == 4) dy = -1;
    if (dir == 6) dx = +1;

    if (!dx && !dy) throw verror;
    res.push_back( {pos.x()+dx, pos.y()+dy} );

    return res;
}
//=======================================================================================
std::vector<QPoint> land_of(const QJsonObject& obj)
{
    auto pos_o = obj[position_n].toObject();
    QPoint pos( floor(pos_o["x"].toDouble()), floor(pos_o["y"].toDouble()) );
    auto name = obj[name_n].toString();

    if (name == straight_rail_n)
        return land_of_straight_rail(obj, pos);

    if (name == curved_rail_n)
        return land_of_curved_rail(obj, pos);

    if (name == flamethrower_turret_n)
        return land_of_flamethrower_turret(obj, pos);

    if (name == heat_exchanger_n || name == "boiler")
        return land_of_heat_exchanger(obj, pos);

    if (name == "pump" ||
        name == "arithmetic-combinator" ||
        name == "decider-combinator")
    {
        return land_of_direction(obj, pos, 2, 1);
    }
    if (name == "splitter" ||
        name == "fast-splitter" ||
        name == "express-splitter")
    {
        return land_of_direction(obj, pos, 1, 2);
    }

    if ( name == "steam-turbine" || name == "steam-engine" )
    {
        return land_of_direction(obj, pos, 5, 3);
    }

    if (name == "offshore-pump")
        return offshore_pump_land(obj, pos);


    return square_of(name, pos);
}
//=======================================================================================

using QPointSet = QSet<QPoint>;
int qHash(const QPoint& p)
{
    return qHash(p.x() ^ p.y());
}

//=======================================================================================

void process_entity(QPointSet *points, const QJsonObject& obj)
{
    auto name = obj[name_n].toString();
    auto list = land_of(obj);

    for(auto lf: list)
    {
        if (points->contains(lf))
        {
            //  Рельсы пересекаются дай палян.
            if (name.contains("rail"))
                continue;

            //vwarning << lf << name;
        }

        points->insert(lf);
    }
}
//=======================================================================================
QJsonObject BPrint_Landfill::correct_landfill(QJsonObject src)
{
    if (!src.keys().contains(entities_n)) throw verror;
    if (!src[entities_n].isArray()) throw verror;

    auto entities = src[entities_n].toArray();

    QPointSet points;
    for (auto ent: entities)
    {
        process_entity(&points, ent.toObject());
    }
    QJsonArray landfills;
    for ( auto & lf: points )
    {
        QJsonObject p;
        p["x"] = lf.x();
        p["y"] = lf.y();

        QJsonObject np;
        np[name_n] = landfill_n;
        np[position_n] = p;

        landfills.append(np);
    }
    src[tiles_n] = landfills;
    return src;
}
//=======================================================================================
