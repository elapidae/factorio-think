#pragma once

#include <QJsonObject>
#include <QJsonArray>

#include "blueprint.h"
#include "deconstruction_planner.h"
#include "items/icons.h"

//constexpr static auto n_version     = "version";
constexpr static auto n_version_val1 = 281479277379584;
constexpr static auto n_version_val2 = 0x10001005b0000;

//=======================================================================================

class BluePrint_Book
{
public:
    static BluePrint_Book do_import( const QByteArray& arr );
    static BluePrint_Book from_object( QJsonObject obj );

    BluePrint_Book( QString label = "", QString description = "" );
    QJsonObject build() const;
    QJsonObject build_for_export() const;

    void add( const BluePrint& bp );
    void add( const BluePrint_Book& bp );
    void assign( const BluePrint& bp, unsigned idx );
    void assign( const BluePrint_Book& bp, unsigned idx );

    void inc_pos();
    void shift_to( unsigned idx ); // increase cur index to idx pos in line, from 0 to 5.
    void next_line(); // increase cur index to mod 6 == 0

    Icons icons;

    void set_burner_inserters_stack_size_1();

private:
    int active_index = 0;
    qint64 version = n_version_val1;

    QJsonArray blueprints() const;
    std::map<unsigned, BluePrint> blueprints_map;
    std::map<unsigned, Deconstruction_Planner> deconstructions_map;
    std::map<unsigned, BluePrint_Book> books_map;
    QString label;
    QString description;

    unsigned cur_idx = 0;
    unsigned max_idx = 0;
};
//=======================================================================================
