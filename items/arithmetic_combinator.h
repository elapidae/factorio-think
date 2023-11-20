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

    bool replace_in_out( const Item& src, const Item& dst );

    void set_operation(); // not implemented
    void set_second_constant( int val ); // not implemented
};
//=======================================================================================
class Arithmetic_Combinator2
{
public:
    Arithmetic_Combinator2( QJsonValueRef ref ) : ref(ref) {}

    bool replace_in_out( const Item& src, const Item& dst )
    {
        Arithmetic_Combinator ac{ ref.toObject() };
        auto res = ac.replace_in_out( src, dst );
        ref = ac.obj;
        return res;
    }

private:
    QJsonValueRef ref;
};
//=======================================================================================

#endif // ARITHMETIC_COMBINATOR_H
