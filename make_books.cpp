#include "make_books.h"

#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QFile>

#include "blueprint.h"
#include "vlog.h"
#include "vbyte_buffer.h"
#include "vbyte_buffer_view.h"

#define qdeb qDebug() << QByteArray::fromStdString(V_POSITION_FIX.place())
static void copy_to_clipboard( QByteArray arr );

struct Entity
{
    QString label() const { return "[" + type + "=" + name + "]"; }

    QJsonObject item_object() const
    {
        QJsonObject res;
        res["name"] = name;
        res["type"] = type;
        return res;
    }

    static Entity coal()          { return item_50("coal");           }
    static Entity stone()         { return item_50("stone");          }
    static Entity iron_ore()      { return item_50("iron-ore");       }
    static Entity copper_ore()    { return item_50("copper-ore");     }
    static Entity uranium_ore()   { return item_50("uranium-ore");    }

    static Entity iron_plate()    { return item_100("iron-plate");    }
    static Entity copper_plate()  { return item_100("copper-plate");  }
    static Entity steel_plate()   { return item_100("steel-plate");   }

    static Entity plastic_bar()         { return item_100("plastic-bar");           }
    static Entity electronic_circuit()  { return item(200, "electronic-circuit");   }


    static Entity train_stop()    { return item(-1, "train-stop");    }

    static Entity water()           { return fluid("water");            }
    static Entity crude_oil()       { return fluid("crude-oil");        }
    static Entity steam()           { return fluid("steam");            }
    static Entity heavy_oil()       { return fluid("heavy-oil");        }
    static Entity light_oil()       { return fluid("light-oil");        }
    static Entity petroleum_gas()   { return fluid("petroleum-gas");    }
    static Entity sulfuric_acid()   { return fluid("sulfuric-acid");    }
    static Entity lubricant()       { return fluid("lubricant");        }

    static Entity virtual_signal( QString name )
    {
        return { -1, "virtual", "signal-" + name };
    }

    int optimum_station_count() const
    {
        if ( type == "fluid" ) return 20000;
        if ( stack_size <= 0 ) throw verror;

        auto cells_in_chest = 16;
        auto chests_count = 12;
        return stack_size * chests_count * cells_in_chest / 2;
    }

    //QString type() const { return type; }
    //QString name() const { return name; }

private:
    int     stack_size = 50;
    QString type       = "item";
    QString name       = "coal";

    Entity( int s, QString t, QString n )
        : stack_size( s )
        , type( t )
        , name( n )
    {}

private:
    static Entity item_50( QString name )
    {
        return item( 50, name );
    }
    static Entity item_100( QString name )
    {
        return item( 100, name );
    }
    static Entity item( int stack_size, QString name )
    {
        return { stack_size, "item", name };
    }
    static Entity fluid( QString name )
    {
        return { 25000, "fluid", name };
    }
};
//=======================================================================================
static auto mining_entities = []
{
    QList<Entity> res;
    res.append( Entity::coal()        );
    res.append( Entity::stone()       );
    res.append( Entity::iron_ore()    );
    res.append( Entity::copper_ore()  );
    res.append( Entity::uranium_ore() );

    return res;
}();
//=======================================================================================
static auto second_entities = []
{
    QList<Entity> res;

    res.append( Entity::iron_plate()  );
    res.append( Entity::copper_plate());
    res.append( Entity::steel_plate() );

    res.append( Entity::plastic_bar() );
    res.append( Entity::electronic_circuit() );

    return res;
}();
//---------------------------------------------------------------------------------------
static auto fluid_entities = []
{
    QList<Entity> res;
    res.append( Entity::water()         );
    res.append( Entity::crude_oil()     );
    res.append( Entity::steam()         );
    res.append( Entity::heavy_oil()     );
    res.append( Entity::light_oil()     );

    res.append( Entity::petroleum_gas() );
    res.append( Entity::sulfuric_acid() );
    res.append( Entity::lubricant()     );

    return res;
}();


//=======================================================================================
static bool is_tolerant_entity( QString name )
{
    if ( name == "" ) throw verror;

    if ( name == "transport-belt" ) return true;
    if ( name == "underground-belt" ) return true;
    if ( name == "fast-inserter" ) return true;
    if ( name == "straight-rail" ) return true;
    if ( name == "curved-rail" ) return true;
    if ( name == "roboport" ) return true;
    if ( name == "splitter" ) return true;
    if ( name == "rail-chain-signal" ) return true;
    if ( name == "big-electric-pole" ) return true;
    if ( name == "medium-electric-pole" ) return true;
    if ( name == "wooden-chest" ) return true;
    if ( name == "burner-inserter" ) return true;
    if ( name == "logistic-chest-requester" ) return true;
    if ( name == "inserter" ) return true;
    if ( name == "small-lamp" ) return true;
    if ( name == "pump" ) return true;
    if ( name == "storage-tank" ) return true;
    if ( name == "pipe" ) return true;
    if ( name == "pipe-to-ground" ) return true;
    if ( name == "express-transport-belt" ) return true;
    if ( name == "express-underground-belt" ) return true;
    if ( name == "stack-inserter" ) return true;
    if ( name == "fluid-wagon" ) return true;
    if ( name == "locomotive" ) return true;
    if ( name == "cargo-wagon" ) return true;
    if ( name == "steel-furnace" ) return true;
    if ( name == "" ) return true;
    if ( name == "" ) return true;
    if ( name == "" ) return true;
    if ( name == "" ) return true;
    if ( name == "" ) return true;
    if ( name == "" ) return true;

    return false;
}
//=======================================================================================
constexpr auto n_version     = "version";
constexpr auto n_version_val1 = 281479277379584;
constexpr auto n_version_val2 = 0x10001005b0000;
constexpr auto n_item        = "item";
constexpr auto n_item_val    = "blueprint";
constexpr auto n_label       = "label";
constexpr auto n_entities    = "entities";
constexpr auto n_icons       = "icons";
constexpr auto n_signal      = "signal";
void check_version( quint64 ver )
{
    if ( ver == n_version_val1 ) return;
    if ( ver == n_version_val2 ) return;
    vbyte_buffer bb;
    bb.append_LE( ver );
    auto v = bb.view();
    throw verror << v.u16_LE() << "."
                 << v.u16_LE() << "."
                 << v.u16_LE() << "."
                 << v.u16_LE();
}
// version:  281479277379584
// item:     "blueprint"
// label:    "name"
// entities: array
// icons:    array
//---------------------------------------------------------------------------------------
QJsonObject process_one_entity( QJsonObject entity, Entity src, Entity dst )
{
    auto name = entity["name"].toString();

    if ( is_tolerant_entity(name) )
    {
        return entity;
    }

    if ( name == "constant-combinator" )
    {
        auto behavior = entity["control_behavior"].toObject();
        auto src_filters = behavior["filters"].toArray();
        QJsonArray filters;
        while ( !src_filters.isEmpty() )
        {
            auto item = src_filters.takeAt(0).toObject();
            auto sig = item["signal"].toObject();
            if ( sig == src.item_object() )
                sig = dst.item_object();
            item["signal"] = sig;
            filters.append( item );
        }
        behavior["filters"] = filters;
        entity["control_behavior"] = behavior;
        return entity;
    } // if ( name == "constant-combinator" )

    if ( name == "decider-combinator" )
    {
        constexpr auto n_control_behavior = "control_behavior";
        constexpr auto n_decider_conditions = "decider_conditions";

        { // control_behavior
            auto control_behavior = entity[n_control_behavior].toObject();
            { // conditions
                auto conditions = control_behavior[n_decider_conditions].toObject();
                conditions["constant"] = dst.optimum_station_count();

                { // first_signal
                    auto signal = conditions["first_signal"].toObject();
                    if ( signal == src.item_object() )
                        conditions["first_signal"] = dst.item_object();
                } // first_signal

                control_behavior[n_decider_conditions] = conditions;
            } // conditions

            entity[n_control_behavior] = control_behavior;
        } // control_behavior

        return entity;
    } // if ( name == "decider-combinator" )

    if ( name == "train-stop" )
    {
        auto station = entity["station"].toString();
        station.replace( src.label(), dst.label() );
        entity["station"] = station;

        return entity;
    } // if ( name == "train-stop" )

    qdeb << entity;
    copy_to_clipboard( QJsonDocument(entity).toJson() );
    throw verror;
}
//---------------------------------------------------------------------------------------
static void add_landfill( QJsonObject *bp_ptr )
{
    *bp_ptr = BluePrint::correct_landfill( *bp_ptr );
}
//---------------------------------------------------------------------------------------
static void correct_schedules( QJsonObject *bp_ptr, Entity src, Entity dst )
{
    auto &bp = *bp_ptr;
    if ( !bp.contains("schedules") ) return;

    auto src_schedules = bp["schedules"].toArray();
    QJsonArray schedules;
    while ( !src_schedules.isEmpty() )
    {
        auto sch_obj = src_schedules.takeAt(0).toObject();
        {
            auto src_sch_arr = sch_obj["schedule"].toArray();
            QJsonArray sch_arr;
            while( !src_sch_arr.isEmpty() )
            {
                auto sch = src_sch_arr.takeAt(0).toObject();
                auto station = sch["station"].toString();
                station.replace( src.label(), dst.label() );
                sch["station"] = station;
                sch_arr.append( sch );
            } // while( !src_sch_arr.isEmpty() )
            sch_obj["schedule"] = sch_arr;
        }
        schedules.append( sch_obj );
    } // while ( !src_schedules.isEmpty() )
    bp["schedules"] = schedules;
}
//---------------------------------------------------------------------------------------
QJsonObject change_blueprint( QJsonObject blueprint, Entity src, Entity dst )
{
    correct_schedules( &blueprint, src, dst );
    check_version( blueprint[n_version].toDouble() );

    if ( blueprint[n_item].toString() != n_item_val ) throw verror;

    auto name = blueprint[n_label].toString();
    name.replace(src.label(), dst.label());
    blueprint[n_label] = name;

    auto src_icons = blueprint[n_icons].toArray();
    QJsonArray icons;
    while ( !src_icons.isEmpty() )
    {
        auto icon = src_icons.takeAt(0).toObject();
        auto sig = icon[n_signal].toObject();
        if ( sig == src.item_object() )
        {
            icon[n_signal] = dst.item_object();
        }
        icons.append( icon );
    }
    blueprint[n_icons] = icons;

    auto src_entities = blueprint[n_entities].toArray();
    QJsonArray entities;
    while ( !src_entities.isEmpty() )
    {
        auto entity = src_entities.takeAt(0).toObject();
        entity = process_one_entity( entity, src, dst );
        entities.append( entity );
    } // while ( !src_entities.isEmpty() )
    blueprint[n_entities] = entities;

    add_landfill( &blueprint );
    return blueprint;
}
//=======================================================================================
static QJsonObject make_book( QString label, QString description )
{
    QJsonObject res;
    res["active_index"] = 0;
    res["blueprints"] = QJsonArray();
    res["icons"] = QJsonArray();
    res["item"] = "blueprint-book";
    res["label"] = label;
    res["description"] = description;
    res[n_version] = double( n_version_val1 );
    return res;
}
//=======================================================================================
static QJsonObject make_train_book()
{
    auto res = make_book( "Trains", "Auto generated train stops." );
    QJsonArray icons;

    QJsonObject obj;

    obj["index"] = 1;
    obj["signal"] = Entity::train_stop().item_object();
    icons.append( obj );

    obj["index"] = 2;
    obj["signal"] = Entity::virtual_signal("1").item_object();
    icons.append( obj );

    res["icons"] = icons;
    return res;
}
//=======================================================================================
static QJsonObject make_fluid_book()
{
    auto res = make_book( "Trains", "Auto generated train stops." );
    QJsonArray icons;

    QJsonObject obj;

    obj["index"] = 1;
    obj["signal"] = Entity::train_stop().item_object();
    icons.append( obj );

    obj["index"] = 2;
    obj["signal"] = Entity::water().item_object();
    icons.append( obj );

    res["icons"] = icons;
    return res;
}
//=======================================================================================
static void copy_to_clipboard( QByteArray arr )
{
    {
        QFile f("clipboard.txt");
        if ( !f.open(QIODevice::WriteOnly) ) throw verror;
        f.write( arr );
    }
    system("cat clipboard.txt | xclip -selection clipboard");
    return;
}
//=======================================================================================
static QJsonObject extract_blueprint( QByteArray src )
{
    auto _obj = BluePrint::extract( src );
    auto obj = _obj["blueprint"];
    if ( !obj.isObject() ) throw verror;
    return obj.toObject();
}
//=======================================================================================
static const char * water_R1();
static const char * water_tSw1();
static void make_fluid()
{
    auto book = make_fluid_book();
    int idx = 0;
    QJsonArray blueprints;

    auto water_r1 = extract_blueprint( water_R1() );
    auto water_s1 = extract_blueprint( water_tSw1() );
    //copy_to_clipboard( QJsonDocument(water_s).toJson() );
    //return;
    for ( auto & dst: fluid_entities )
    {
        QJsonObject obj;
        obj["index"] = idx;
        obj["blueprint"] = change_blueprint( water_r1, Entity::water(), dst );
        blueprints.append( obj );
        obj["index"] = idx + 1;
        obj["blueprint"] = change_blueprint( water_s1, Entity::water(), dst );
        blueprints.append( obj );
        idx += 6;
    }
    //-----------------------------------------------------------------------------------
    book["blueprints"] = blueprints;

    QJsonObject res_obj;
    res_obj["blueprint_book"] = book;
    auto arr = BluePrint::pack( res_obj );
    copy_to_clipboard( arr );
    vdeb << "Done";
    return;
}
//=======================================================================================
static QJsonObject make_mining1_book()
{
    auto res = make_book( "Mining trains v1", "Auto generated train stops." );
    QJsonArray icons;

    QJsonObject obj;

    obj["index"] = 1;
    obj["signal"] = Entity::train_stop().item_object();
    icons.append( obj );

    obj["index"] = 2;
    obj["signal"] = Entity::virtual_signal("M").item_object();
    icons.append( obj );

    res["icons"] = icons;
    return res;
}
//---------------------------------------------------------------------------------------
static const char* coal_M1();
static const char* coal_W1();
static const char* coal_S1();
static const char* coal_R1();
static const char * coal_R_quick4();
static void make_mining()
{
    auto book = make_mining1_book();
    int idx = 0;
    QJsonArray blueprints;

    auto m1 = extract_blueprint( coal_M1() );
    auto w1 = extract_blueprint( coal_W1() );
    auto s1 = extract_blueprint( coal_S1() );
    auto r1 = extract_blueprint( coal_R1() );

    for ( auto & dst: second_entities )
    {
        QJsonObject obj;
        obj["index"] = idx + 0;
        obj["blueprint"] = change_blueprint( m1, Entity::coal(), dst );
        blueprints.append( obj );
        obj["index"] = idx + 1;
        obj["blueprint"] = change_blueprint( w1, Entity::coal(), dst );
        blueprints.append( obj );
        obj["index"] = idx + 2;
        obj["blueprint"] = change_blueprint( s1, Entity::coal(), dst );
        blueprints.append( obj );
        obj["index"] = idx + 3;
        obj["blueprint"] = change_blueprint( r1, Entity::coal(), dst );
        blueprints.append( obj );
        idx += 6;
    }
    //-----------------------------------------------------------------------------------
    book["blueprints"] = blueprints;

    QJsonObject res_obj;
    res_obj["blueprint_book"] = book;
    auto arr = BluePrint::pack( res_obj );
    copy_to_clipboard( arr );
    //vdeb << arr;
    vdeb << "Done";
    return;
}

//=======================================================================================
void replace_train_stops( QJsonArray* entities, Entity src, Entity dst )
{
    for ( int i = 0; i < entities->count(); ++i )
    {
        auto entity = entities->at(i).toObject();
        auto name = entity["name"].toString();
        if ( name != "train-stop" ) continue;

        auto station = entity["station"].toString();
        station.replace( src.label(), dst.label() );
        entity["station"] = station;
    }
}
//=======================================================================================
static QJsonObject make_product1_book()
{
    auto res = make_book( "Product 1", "Auto generated burnings." );
    QJsonArray icons;

    QJsonObject obj;

    obj["index"] = 1;
    obj["signal"] = Entity::train_stop().item_object();
    icons.append( obj );

    obj["index"] = 2;
    obj["signal"] = Entity::virtual_signal("P").item_object();
    icons.append( obj );

    obj["index"] = 3;
    obj["signal"] = Entity::coal().item_object();
    icons.append( obj );

    obj["index"] = 4;
    obj["signal"] = Entity::virtual_signal("1").item_object();
    icons.append( obj );

    res["icons"] = icons;
    return res;
}
//=======================================================================================
static const char * product_iron1();
static void make_product1()
{
    auto book = make_product1_book();
    int idx = 0;
    QJsonArray blueprints;

    auto p1 = extract_blueprint( product_iron1() );

    QJsonObject obj;
    //-----------------------------------------------------------------------------------
    obj["index"] = idx;
    obj["blueprint"] = p1;
    blueprints.append( obj );
    idx += 1;
    //-----------------------------------------------------------------------------------
    obj["index"] = idx;
    auto p2 = change_blueprint( p1, Entity::iron_ore(), Entity::copper_ore() );
    p2 = change_blueprint( p2, Entity::iron_plate(), Entity::copper_plate() );
    obj["blueprint"] = p2;
    blueprints.append( obj );
    idx += 1;
    //-----------------------------------------------------------------------------------
    obj["index"] = idx;
    p1 = change_blueprint( p1, Entity::iron_plate(), Entity::steel_plate() );
    p1 = change_blueprint( p1, Entity::iron_ore(),   Entity::iron_plate() );
    obj["blueprint"] = p1;
    blueprints.append( obj );
//    idx += 1;
    //-----------------------------------------------------------------------------------
    book["blueprints"] = blueprints;

    QJsonObject res_obj;
    res_obj["blueprint_book"] = book;
    auto arr = BluePrint::pack( res_obj );
    copy_to_clipboard( arr );
    vdeb << arr;
    vdeb << "Done";
    return;
}
//=======================================================================================
void make_books()
{
    make_fluid();
    return;

    make_mining();
    return;

    make_product1();
    return;
}
//=======================================================================================
static const char * coal_M1()
{
return R"__(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
)__";
}
static const char * coal_S1()
{
return R"__(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
)__";
}
static const char * coal_W1()
{
return R"__(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
)__";
}
static const char * coal_R1()
{
return R"__(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
)__";
}
//=======================================================================================
static const char * coal_R_quick4()
{
return
R"(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
)";
}
//=======================================================================================
static const char * water_R1()
{
return
R"(0eNrtWVuPozYY/S9+hhHY5hK02x9R9W01QoQ4GWu51Zi00Sj/vTZOuCR2YphUK1Wdh4kg+NjfxeecmE+wLTrSMFpxkHwCmtdVC5Ifn6Clhyor5D1+aghIAOWkBA6oslJecZbRym153YCzA2i1I3+DxD87moFHyngn7gxj1RPu75ORUDtyX3R0N477K+OETQahRdP5k5H4/O4AUnHKKVHh9hentOrKrZgj8YfReceOZOeKcCVkU7diTF3J+QSOG4QOOIEkFOsHO8pIrr7EcmU3kHBckEze4YMbQZECDeaggQYU2a7TU5DxHDLSQOJpjau2qRl3t6TgGlSM3oLLUt+CswYrGLA6kXh2YLX4fI6G32To176rmo4DDXg4gLN6W8t1akDhRkGGuuVF9qHC8Emo8ZJQRzS7UDdjqKK+bv7Rbz7V+ZpEDujR200PQQ247w3oW3pwSSEeZjR3m7ogOnR4wRbIFRF9vK07JjcRQu86dH9dD4TTxNQdN2TGH7eVpC6eVdzN63JLq4zX7GHq75PjSAzO6iLdko/sSAWAGLWnheAdAys+JLdchMp7Mhlo7l3XOz5a1zy2OcJLc4RfmiMTjd+lxzekJ1jGcpE3X3Oowwyt6RhfcrGx2EqRPSqyR43tUX171I01KtpYo0LPHjWyR/XtUe2rBe0lGdlXCyJ7VPtqQWyNChdUK7BHXVAt+70FF1QrWmqgIvTc7cB4nbRG3i0z6lgGjnts27GKMJdWLWGS/x5o3z021rNuTlneUZ6K73YD1J6ylqfWQkWOhJ34B60OipKVPoDEkxdlk7FeIxLwHZzV95VaVCuxffnvwAippiZakH2Cei7XOVZvlR+IfCujhEaiKOoDbbnwMfkHaUWrkD878anPvDefxTpKuOkVC1zA06kMXjVtWFDV5QXJmLvviCzDVf3OOteERmp61DGeuWN0oCMzlWRHu/Kp10PxfAL78gcqMTODKIwmirXRjuTWdGWj1YqhQhZxTlmtZtmBuKKnf2rFYl74O6NjGS2arKK/EZm6f6TGhjbalM9YQAcRWUcHr1BwcfVu4olN8cSLW8pf21LR7aIEuV4ZUF77mpbT/yZBIy3vSE4FCz3xw7Fhlxnc8AV05OX2ATGb3fGViqEn/m7o+JsYoRx/uuikJq+bU9pTT7pndZkqJk32WdGSZQQvW8IB0PgA9m7qhUNDE+GJZyyzonCLTEsCML6j6S9J4uM8PRBCB3QtEVMUtWwyzjpiyBwju7u0BPLsSZ/Sm4aGNwkMoCmBvo1awM0itcBwjZSOkyyUUoz+JSnFaIEHg+F/yINhY7/gVecNlh4MB0uPG6InKvyaI5ltkeU/Dccyzktw0Itw8ItwgkU4qoe05zL9zrJmOM/UdqGObI0/Cm+tnqEXWlLtUl6nPeRFyRw1QSonaMjOfif+IeNvCVdobVrQknJF8RfMy70larJIVu80oGdFsYtUEsCP3i98723Cu8gNoUei3YXRslcYUTjPtq/DjNf9dkN255R4s+LVQ+9tda8evKdOO3oG4c8gXF67KmIdmDcP9snBQACXWh74Cy3Pb1+zPIHZ8hi5IkAr3s0YC7lS7yz7NlgvePB/wft1gidb9etyZ3TlQWhPH8Mbl3v6gHLz9Ps2mbyrd4DwjK16IPZxtIFRhKJNEOPz+R/+8pHU
)";
} // water_R1
//=======================================================================================
static const char * water_tSw1()
{
return
R"(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
)";
}


static const char * product_iron1()
{
return R"(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
)";
}
