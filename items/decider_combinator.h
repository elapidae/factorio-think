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
    void constant( int val );
};
//=======================================================================================

#endif // DECIDER_COMBINATOR_H
