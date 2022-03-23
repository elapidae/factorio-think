#include <QApplication>
#include <string>
#include "vlog.h"
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

#include "blue.h"
#include "parse_lua_recipe.h"
#include "vcat.h"
#include "blueprint.h"

//=======================================================================================
//=======================================================================================
// Задача: сделать присыпку на элементы карты / blueprint-а
// надо расшифровать схему.
//  Определить элементы сьроения и пр. + их кординаты
//  разобраться как делается присыпка
//  понять как определить координаты куда присыпку сыпать
//  добавить присыпку в карту
//  сохранить
//=======================================================================================
//=======================================================================================

auto rail_diag_3 = "0eNqVktFugzAMRf/Fz0FqoJQ1v7HHaZpocVtLwaBgqiGUf28C64qmbhqPdnx8700ywsH22DpiATMCHRvuwLyN0NGZSxt7MrQIBkiwBgVc1rFyJVnwCogr/ASjvXqCXMlJHzrf1DyRvC7IdBWZLcjMvytAFhLC2fNUDB/c1wd0wdSDluD3fJFksq2gbbpANRwVw6YiVzCASfQ+5ICKHB7nUx0lhOzX/p/Y9o6FEHcpW3J1IhsvZ/xdJ1sLrFbQ/wR2fyqE+NO7m8U3UXBF100r0he9LfZpketcZ7uN9zd9hL1F";

auto rail_diag_2 = "0eNqVktFugzAMRf/Fz0Fqkna0+Y09VtVES9pZCgYFUw2h/HsTGB3apmk82vHxvTfJAGfX2cYjMZgB8FJTC+Y4QIs3Klzqcd9YMIBsKxBARZUqX6CDIACptB9gZBC/IHf03MXOk5omstcFqVaRakHqcBJgiZHRTp7Hon+jrjpbH0190Rz93t45G20LaOo2UjUlxbhprwX0YDJ5iDmgRG8v02meJBjd5/7vmJyxGGKWcgWVV3Tpcn4Cagb0WmC1gvwnoP9UiPHHdzeLbyLgbn07rlB7uc0PKt/JndQvmxAeeue9Pw==";

//  На самом деле, при поворотах.
auto rail_d10 = rail_diag_3;
auto rail_d11 = "0eNqdktFuwjAMRf/Fz6m0pAVGfmVCqFCPWUrdKnURVZV/X5qiUaENwR7t5Nx7Y2eEg+ux9cQCdgQ6NtyB/RihoxOXburJ0CJYIMEaFHBZT5UvyUFQQFzhBawO6hfkTF762Pmh5huZXpDm32QedgqQhYRwzpyKYc99fUAfQ91oiXlPX5Kl2ArapotUw5NjVFrnCgawmd7mUb4ij8f5NFkIuav+PWaW2NXKlVx9kpuGM/7tU7wKvOxgngSKhw7x+WnvdvFNFJzRd0nCvOtiszWblV7pfP0Wwjc1RL0Y";

auto rail_d12 = "0eNqVktFugzAMRf/Fz0FaQhklvzJVEy1eZykYFEw1hPLvS6Db0DZN49FOzr03dmY4uxF7TyxgZ6BLxwPYpxkGunLtUk+mHsECCbaggOs2Vb4mB0EBcYNvYHVQvyA38jLGzie13sj0hjS7SLMh83BSgCwkhGvmpZieeWzP6GOoL1pi3uurZEtsBX03RKrj5BiVikrBBDbTVR7lG/J4WU+LZCHk7vrfsXKL3a1czc0LuTScn8DxAzjsBXY7mH8C1Z8O8fnL3u3mmyi4oR8WCXPUh7IyZaELnT8+hPAOTW29NA==";

auto rail_d13 = "0eNqVktFugzAMRf/Fz0FayChrfmWqJlq8zlIwKJhqCOXfm8DY0DZN49GOj++9SSY4uwE7TyxgJ6BLyz3Y5wl6unLlUk/GDsECCTaggKsmVb4iB0EBcY3vYHVQvyA38jLEzie1TGR6Q+a7SLMhTTgpQBYSwsXzXIwvPDRn9NHUFy3R7/VNstm2gq7tI9VyUoybCqNgBJvpY8wBNXm8LKdlkhByH/u/Y3rFYohVylVcv5JLl/MTyFfA7AV2K+h/AuZPhRh/fne7+SYKbuj7eUX+pB/LY14WutDm8BDCHS9WvQw=";

auto rail_h6 = "0eNqVkdsKgkAQht9lrldoK7P2CXqHiNCcamAdZR0jkX33Vu1ERNTlHL7/Y5gOMttg5YgFTAe0L7kGs+mgpiOntu9JWyEYIMECFHBa9JVLyYJXQJzjBYz26gNyJidN6DyocSNav5BTv1WALCSEo3ko2h03RYYuRD9pCdbjSaJBrqAq60CV3BtD0jxstmAivUpCfE4O9+N0UAjZW/47NrljS/9Q2ZTzA9n+xC9A8iOg/zXor4ZwzfAM8/I7BWd09XjuUs+T1TSJdaxni4n3Vy1Vmvs=";

auto rail_h4_ = "0eNqVkd0KwjAMRt8l1x2YOZ32VURkatVAl40uE8fou9tu/iEiepnwne+QtoetbU3tiAV0D7SruAG96qGhIxc27qSrDWggMSUo4KKMkyvIgldAvDcX0OjVB+RMTtqweVBjIsleyNSvFRgWEjKjeRi6Dbfl1rhQ/aQlWI8nSQa5grpqAlVxNIamLCQ70Aku0cdSIXtrfA9O7sHUP8ptwfsD2XjUFwB/BPBfA341hGuG59cvv6XgbFwzVKQLzPJlms9whtP5xPsrXL6WLA==";

auto rail_h2 = "0eNqVkd1qwzAMRt/lu3ZgTtd49auMMtLG7QSOEhylLAS/+5xk/aGU0l1K9vmOhEbsfO/aQCywI2jfcAf7OaKjI5d+6snQOliQuBoKXNZTFUryiArElfuB1VE9QE4UpE+dC7X8yIobMo9bBcdCQm4xz8XwxX29cyFFX2lJ1uO3ZLNcoW26RDU8GVPSyigMsJnepGlQUXD75XVWCPm//HusOGN5vKh8ydWB/LTiE0C/CJj/GsxTQ9pmPoa9uZ3CyYVuWfdDv5tNbtZ6rVfFW4y/ERqa5A==";
//=======================================================================================
int main()
{
    auto d2 = BluePrint::extract(rail_h2);
    vdeb << QJsonDocument(d2).toJson();
    return 0;
}
//=======================================================================================

//=======================================================================================
auto test_path = "/home/el/red/factorio/bin/x64";
//auto test_blue = "test-water";
auto test_blue = "2022-03-21--9-roboports,lamps,turrets.txt";

auto read_blue = [](auto fname)// -> QByteArray
{
    QFile f(fname);
    if (!f.open(QIODevice::ReadOnly)) throw verror;
    return f.readAll();
};
//=======================================================================================
auto blueprint_n = "blueprint";
auto icons = "icons";
auto version = "version";
auto item = "item";
auto entities_n = "entities";
auto tiles_n = "tiles";

int __main(int c, char**v)
{
    QApplication a(c,v);

    auto code = read_blue(QString(test_path) + "/" + test_blue);
    //vdeb << code;
    auto obj = BluePrint::extract(code);
    //vdeb << obj.keys();
    //throw;
    auto _bp_o = obj[blueprint_n];
    Q_ASSERT(_bp_o.isObject());
    auto o = _bp_o.toObject();

    auto landfill = BluePrint::correct_landfill(o);

    QJsonObject res_obj;
    res_obj[blueprint_n] = landfill;

    auto packed = BluePrint::pack(res_obj);
    throw verror << packed;
    //auto unpacked = BluePrint::extract(packed);

    //throw verror << unpacked.keys();

    //throw verror << QJsonDocument(res_obj).toJson(QJsonDocument::Compact);

    auto gen_keys = o.keys();
    vdeb << gen_keys;
    QJsonObject blueprint_obj;    
    for (auto& k: gen_keys)
    {
        if (k == icons)     { blueprint_obj[k] = o[k]; continue; }
        if (k == version)   { blueprint_obj[k] = o[k]; continue; }
        if (k == item)      { blueprint_obj[k] = o[k]; continue; }
        //if (k == entities) { blueprint_obj[k] = o[k]; continue; }
        //      { blueprint_obj[k] = o[k]; continue; }

        //if (k == tiles_n)     continue;
        //if (k == entities_n)  continue;

        vwarning << k << QJsonDocument(o[k].toArray()).toJson()
                 << QJsonDocument(o[k].toObject()).toJson();;
        if (!o[k].isArray()) throw verror << k << "ARR";

        throw verror;
    }

    QJsonDocument doc(blueprint_obj);
    vdeb;
    vdeb;
    vdeb << doc.toJson();

    //return a.exec();
}
//=======================================================================================



//=======================================================================================
int _main(int c, char**v)
{
    QApplication a(c,v);
    blue b;
    return a.exec();


    auto recipes = parse_lua_recipe::interpret();
    //for ( auto r: recipes ) vdeb << r.str();

    vdeb;
    for ( auto r: recipes )
    {
        if ( r.ingredients.contains("pipe") )
            vdeb << r.str();
    }
    return 0;
}
//=======================================================================================

/*
 *  Поиск одинаковых рецептов. Их немного.
    while ( recipes.size() )
    {
        auto base = recipes.takeFirst();
        auto base_sign = base.ing_sign();
        vdeb << "===============================================================";
        vdeb << "Base:" << base.name << " -- " << base.ing_sign();

        for ( int i = 0; i < recipes.size(); )
        {
            auto cur = recipes.at(i);

            if ( cur.ing_sign() != base_sign ) { ++i; continue; }
            vdeb << "\tfound:" << cur.name;
            recipes.takeAt(i);
        }

    } // all recipes
*/
