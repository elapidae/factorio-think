#include "control_behavior.h"

#include "names.h"

//=======================================================================================
int Circuit_Condition::constant() const
{
    auto obj = ref.toObject();
    return obj["constant"].toInt();
}
//=======================================================================================
void Circuit_Condition::constant( int val )
{
    auto obj = ref.toObject();
    obj["constant"] = val;
    ref = obj;
}
//=======================================================================================
Filters Control_Behavior::filters()
{
    throw verror;
}
//=======================================================================================
void Control_Behavior::filters( Filters f )
{
    throw verror; (void)f;
}
//=======================================================================================
void Control_Behavior::circuit_condition_constant( int val )
{
    auto obj = ref.toObject();
    Circuit_Condition cc { obj[names::circuit_condition] };
    cc.constant( val );
    ref = obj;
}
//=======================================================================================
