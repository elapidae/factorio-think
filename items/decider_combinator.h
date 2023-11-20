#ifndef DECIDER_COMBINATOR_H
#define DECIDER_COMBINATOR_H

#include "item.h"
#include "names.h"

//=======================================================================================
namespace names
{

}
//=======================================================================================
class Decider_Combinator
{
public:
    QJsonObject obj;

    void first_signal( Item item );
    QString first_signal_name() const;
    void constant( int val );
};
//=======================================================================================
class Decider_Combinator2
{
public:
    Decider_Combinator2( QJsonValueRef ref ) : ref(ref) {}

    void replace_first_signal( const Item& src, const Item& dst )
    {
        Decider_Combinator dc{ ref.toObject() };
        if ( dc.first_signal_name() != src.name ) return;
        dc.first_signal( dst );
        ref = dc.obj;
    }

private:
    QJsonValueRef ref;
};
//=======================================================================================


#endif // DECIDER_COMBINATOR_H
