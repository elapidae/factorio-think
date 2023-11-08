#ifndef ARITHMETIC_COMBINATOR_H
#define ARITHMETIC_COMBINATOR_H

#include "names.h"
#include "item.h"

//=======================================================================================
class Arithmetic_Combinator
{
public:
    QJsonObject obj;

    void first_signal( const Item& item );
    void output_signal( const Item& item );

    void set_operation(); // not implemented
    void set_second_constant( int val ); // not implemented
};
//=======================================================================================

#endif // ARITHMETIC_COMBINATOR_H
