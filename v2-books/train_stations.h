#pragma once

#include "blueprint_book.h"

//=======================================================================================
//  Train Stations ver.2 for making unified schemes.
class Train_Stations
{
public:
    static BluePrint_Book R_solid_intermediate_stops();
    static BluePrint_Book S_solid_intermediate_stops();

    static BluePrint_Book RS_fluid_intermediate_stops();

    static BluePrint_Book book();
};
//=======================================================================================
