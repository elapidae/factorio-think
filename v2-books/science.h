#ifndef SCIENCE_H
#define SCIENCE_H

#include "blueprint_book.h"

//=======================================================================================
class Science
{
public:
    static BluePrint five_science_labs();

    // 2024-06-09
    // City block with all seven scene packets, but not used in middle level.
    static BluePrint city_science_v1();

    // some raw book
    static BluePrint_Book book();
};
//=======================================================================================

#endif // SCIENCE_H
