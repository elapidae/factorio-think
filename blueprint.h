#pragma once

#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include "items/icons.h"
#include "item.h"

static constexpr auto n_blueprint   = "blueprint";

static constexpr auto n_entities    = "entities";
static constexpr auto n_item        = "item";
static constexpr auto n_icons       = "icons";
static constexpr auto n_schedules   = "schedules";
static constexpr auto n_version     = "version";
static constexpr auto n_tiles       = "tiles";
//static constexpr auto n_     = "";
//static constexpr auto n_     = "";


//=======================================================================================
class BluePrint
{
public:
    BluePrint() {} // invalid
    static BluePrint do_import( QByteArray raw0 );
    QByteArray do_export() const; // as ready copy-paste bp.

    explicit BluePrint( QJsonObject bp );
    QJsonObject build() const;

    QList<QJsonValueRef> find( Item item );

    //  find & control that has only one item.
    QJsonValueRef find_unique( Item item );

    // override all burner inserters stack size == 1
    void set_burner_inserters_stack_size_1();

    QJsonArray  entities;
    Icons       icons;
    QJsonArray  schedules;
    quint64     version = 0;

    QJsonArray  tiles;
};
//=======================================================================================
