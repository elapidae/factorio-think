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

//=======================================================================================
int main()
{
    auto d2 = BluePrint::extract(rail_diag_2);
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
