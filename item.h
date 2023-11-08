#pragma once

#include <QJsonObject>

//=======================================================================================
class Item
{
public:
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

    struct Named
    {
        static Item train_stop() { return get("train-stop"); }
        static Item locomotive() { return get("locomotive"); }

        static Item coal()       { return get("coal"); }
        static Item virtual_signal( QString name ) { return Item::virtual_signal(name); }
    };

    static Item stone()         { return item(50, "stone");          }
    static Item iron_ore()      { return item(50, "iron-ore");       }
    static Item copper_ore()    { return item(50, "copper-ore");     }
    static Item uranium_ore()   { return item(50, "uranium-ore");    }

    static Item iron_plate()    { return item(100, "iron-plate");    }
    static Item copper_plate()  { return item(100, "copper-plate");  }
    static Item steel_plate()   { return item(100, "steel-plate");   }

    static Item plastic_bar()         { return item(100, "plastic-bar");          }
    static Item electronic_circuit()  { return item(200, "electronic-circuit");   }


    static Item train_stop()    { return item(-1, "train-stop");    }

    static Item water()           { return fluid("water");            }
    static Item crude_oil()       { return fluid("crude-oil");        }
    static Item steam()           { return fluid("steam");            }
    static Item heavy_oil()       { return fluid("heavy-oil");        }
    static Item light_oil()       { return fluid("light-oil");        }
    static Item petroleum_gas()   { return fluid("petroleum-gas");    }
    static Item sulfuric_acid()   { return fluid("sulfuric-acid");    }
    static Item lubricant()       { return fluid("lubricant");        }

    static Item virtual_signal( QString name );

    int optimum_station_count() const;

    Item() {} // invalid.
    Item( const QJsonObject& o );
private:
    Item( int s, QString t, QString n );
public:
    int     stack_size = -1;
    QString item_type  = "";
    QString type       = "bad";
    QString name       = "ent";

private:
    static Item item( int stack_size, QString name );
    static Item fluid( QString name );
};
//=======================================================================================
