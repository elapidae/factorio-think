#pragma once

#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include "items/icons.h"
#include "items/trains.h"
#include "item.h"


//=======================================================================================
class BluePrint
{
public:
    static void test_positions();

    BluePrint(); // invalid
    static BluePrint do_import( QByteArray raw0 );
    QByteArray do_export() const; // as ready copy-paste bp.
    QByteArray do_export_landfill() const; // as ready copy-paste bp.


    explicit BluePrint( QJsonObject bp );
    QJsonObject build() const;

    void merge( BluePrint bp );

    QList<QJsonValueRef> find( Item item );
    QList<QJsonValueRef> find_assembling_machines();
    QList<QJsonValueRef> find_inserters();
    QList<QJsonValueRef> find_decider_combinators();

    //  find & control that has only one item.
    QJsonValueRef find_unique( Item item );

    // override all burner inserters stack size == 1
    void set_burner_inserters_stack_size_1();

    void arithmetic_combinators_replace_in_out( Item src, Item dst );

    void constant_combinators_replace( Item src, Item dst );
    void decider_combinators_replace_first_signal_count( const Item& src,
                                                   const Item& dst, int count = -1 );


    void locomotives_init_fuel_coal( int count );
    void locomotives_init_fuel_nuclear( int count );
    void train_stops_replace( Item src, Item dst );

    // Find items and remove field from object.
    void remove_field( Item item, QString field );

    void shift( int x, int y );

    QString description;
    QString label;

    QJsonArray  entities;
    Icons       icons;
    Schedules   schedules;
    quint64     version = 0;

    bool absolute_snapping {false};
    QJsonObject position_relative_to_grid;
    QJsonObject snap_to_grid;

    QJsonArray  tiles;
};
//=======================================================================================
