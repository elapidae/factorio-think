#include "science.h"

//=======================================================================================
#include "raw_science.h"
//=======================================================================================


//=======================================================================================
BluePrint Science::five_science_labs()
{
    return BluePrint::do_import( raw_five_labs );
}

BluePrint Science::city_science_v1()
{
    return BluePrint::do_import( raw_science_city_block_v1 );
}

BluePrint_Book Science::book()
{
    return BluePrint_Book::do_import( raw_book );
}
//=======================================================================================
