#pragma once

#include <QJsonObject>

//=======================================================================================
class Item
{
public:
    struct Named;

    static Item get( QString name );
    static QStringList keys();

    QString debug() const { return QString("n:'%1', t:'%2', s:%3")
                            .arg(name).arg(type).arg(stack_size); }
    QString label() const { return "[" + type + "=" + name + "]"; }

    QJsonObject item_name_obj() const
    {
        QJsonObject res;
        res["name"] = name;
        res["type"] = type;
        return res;
    }

    static Item virtual_signal( QString name );

    int optimum_station_count() const;

    int prefer_assemble_count() const { return assemble_count; }
    const Item& prefer_assemble_count(int cnt) { assemble_count = cnt; return *this; }

    Item() {} // invalid.
    Item( const QJsonObject& o );

private:
    Item( int s, QString t, QString n );
public:
    int     stack_size = -1;
    QString item_type  = "";
    QString type       = "bad";
    QString name       = "ent";
    int assemble_count = -1;

private:
    static Item item( int stack_size, QString name );
    static Item fluid( QString name );
};
//=======================================================================================
struct Item::Named
{
    //----
    static Item virtual_signal( QString name ) { return Item::virtual_signal(name); }
    //----
    static Item train_stop()    { return get("train-stop");     }
    static Item locomotive()    { return get("locomotive");     }

    static Item coal()          { return get("coal");           }
    static Item stone()         { return get("stone");          }
    static Item iron_ore()      { return get("iron-ore");       }
    static Item copper_ore()    { return get("copper-ore");     }
    static Item uranium_ore()   { return get("uranium-ore");    }

    static Item iron_plate()    { return get("iron-plate");     }
    static Item copper_plate()  { return get("copper-plate");   }
    static Item steel_plate()   { return get("steel-plate");    }

    static Item plastic_bar()         { return get("plastic-bar");          }
    static Item electronic_circuit()  { return get("electronic-circuit");   }
    static Item battery()             { return get("battery");              }
    static Item sulfur()              { return get("sulfur");               }
    static Item explosives()          { return get("explosives");           }

    static Item water()           { return fluid("water");            }
    static Item crude_oil()       { return fluid("crude-oil");        }
    static Item steam()           { return fluid("steam");            }
    static Item heavy_oil()       { return fluid("heavy-oil");        }
    static Item light_oil()       { return fluid("light-oil");        }
    static Item petroleum_gas()   { return fluid("petroleum-gas");    }
    static Item sulfuric_acid()   { return fluid("sulfuric-acid");    }
    static Item lubricant()       { return fluid("lubricant");        }


    static Item logistic_chest_storage() {
        return get("logistic-chest-storage").prefer_assemble_count(6); }

    static Item repair_pack() {
        return get("repair-pack").prefer_assemble_count(24); }

};
//=======================================================================================
