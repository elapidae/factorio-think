#include "recipe.h"

#include "blueprint_io.h"
#include "blueprint.h"
#include "vlog.h"
#include "items/constant_combinator.h"
#include <QFile>

#include <QDebug>
#define qdeb qDebug() << __FILE__ << __LINE__

//=======================================================================================
static QJsonArray read_recipes()
{
    auto path = "/home/el/red/factorio/script-output/recipe.json";
    QFile f(path);
    if ( !f.open(QIODevice::ReadOnly) ) throw verror;
    return QJsonDocument::fromJson( f.readAll() ).array();
}
//=======================================================================================
static auto recipies = []
{
    QMap<QString, QJsonObject> res;
    auto arr = read_recipes();
    for ( const auto & r: arr )
    {
        auto o = r.toObject();
        res.insert( o["name"].toString(), o );
    }
    return res;
}();
//=======================================================================================
QStringList Recipe::keys()
{
    return recipies.keys();
}
//=======================================================================================
Recipe Recipe::get(QString name)
{
    auto obj = recipies[name];
    Recipe res;
    res.name = obj["name"].toString();
    if ( res.name != name ) throw verror << name;

    auto ing = obj["ingredients"].toArray();
    for ( auto _i: ing ) {
        auto o = _i.toObject();
        Ingredient it;
        it.name = o["name"].toString();
        it.amount = o["amount"].toDouble();
        res.ingredients.push_back( it );
    }

    auto p = obj["products"].toArray();

    if ( p.size() != 1 ) throw verror;
    res.amount = p[0].toObject()["amount"].toDouble();
    auto ckname = p[0].toObject()["name"].toString();

    if ( ckname != name ) throw verror;
    return res;
}
//=======================================================================================
static const char *am2_tmpl();
struct Tmpl
{
    BluePrint bp;
    int machine = -1;
    int chest = -1;
    int inserter = -1;
    int recipe_combinator = -1;
    int count_combinator = -1;

    static Tmpl prepare_tmpl()
    {
        static auto res = _prepare_tmpl();
        return res;
    }

    void apply( QString item, int amount )
    {
        auto it = Item::get( item );
        qdeb << it.debug();
        //return;
        it.type = "item";
        auto m = bp.entities[machine].toObject();
        m["recipe"] = item;
        bp.entities[machine] = m;

        auto c = bp.entities[chest].toObject();
        auto ca = c["request_filters"].toArray();
        auto cao = ca[0].toObject();
        cao["name"] = item;
        ca[0] = cao;
        c["request_filters"] = ca;
        bp.entities[chest] = c;

        Constant_Combinator ccount{ bp.entities[count_combinator].toObject() };
        ccount.set_behavior( 1, it, amount );
        bp.entities[count_combinator] = ccount.obj;

        Constant_Combinator crecipe{ bp.entities[recipe_combinator].toObject() };
        crecipe.save_recipe( Recipe::get(item) );
        bp.entities[recipe_combinator] = crecipe.obj;

        bp.icons.set( 2, it );
    }
private:
    static Tmpl _prepare_tmpl()
    {
        Tmpl res{ BluePrint::do_import(am2_tmpl()) };

        for ( int idx = 0; idx < res.bp.entities.size(); ++idx ) {
            auto o = res.bp.entities[idx].toObject();
            auto name = o["name"].toString();

            if ( name == "assembling-machine-2"  )  { res.machine  = idx; continue; }
            if ( name == "logistic-chest-storage" ) { res.chest    = idx; continue; }
            if ( name == "inserter" )               { res.inserter = idx; continue; }
            if ( name == "constant-combinator" )
            {
                if ( o.keys().contains("control_behavior") )
                    res.count_combinator = idx;
                else
                    res.recipe_combinator = idx;
                continue;
            }
            throw verror;
        } // for ech entry

        return res;
    }
}; // Tmpl
//=======================================================================================
BluePrint Recipe::make_assemble_2(QString iname, int amount)
{
    auto res = Tmpl::prepare_tmpl();
    res.apply( iname, amount );
    return res.bp;
}
//=======================================================================================
QJsonObject Recipe::bp_gen0()
{
    QJsonObject res;



    return res;
}
//=======================================================================================

static const char *am2_tmpl()
{
return R"(
0eNqdlNFugzAMRf/Fz6QqAcaG9idThQJ1qaUQWBKqoSr/voSujImuU/eCcLB9rq8VzlDJAXtNykJxBqo7ZaB4O4OhRgkZzuzYIxRAFluIQIk2RMIYbCtJqmGtqI+kkHFwEZDa4wcUsYv+bGFaISWTou0XhdztIkBlyRJehEzBWKqhrVD7zvclRNB3xhd3KnB9Q5bwTRbB6N/ibJN5ksaa+pWAFYjPINk1ZCzVrD6isczYTosG76P4hPJuKqxDigk5cXg0GlEtJ6M9FMlCQIgzt3OT1PfBI8sDSYv64sfV4Vs+BuIQNrn19euRkrmGlEHtW94fIrkOYXUnywqP4kSdDok16XogW/pv+7n6QNprXW39RNoO/uRb8JTBhBqt31oDF4axYlIegrYXWtiAgldwjxjJg3E3Rk9n+hXFPKYiNWFuuBD/cOFGx+z/Hfmvvi4X/dD1+do7S7eLO7h73Dl/+yZMsfgvRHDymqZR+HOc5i88z5/SOOfPzn0CKXpsMA==
)";
};
