#ifndef ELECTRICITY_H
#define ELECTRICITY_H

#include "blueprint_book.h"

//=======================================================================================
class Electricity
{
public:
    static BluePrint L0_electric_station_40pcs();

    static BluePrint accumulator_block();
    static BluePrint solar_panel_block();

    static BluePrint first_nuclear_x3();

    static BluePrint_Book tier1();
};
//=======================================================================================

#endif // ELECTRICITY_H
