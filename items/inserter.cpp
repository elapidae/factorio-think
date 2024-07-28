#include "inserter.h"

#include "vlog.h"
#include "qdeb.h"
#include "names.h"

//=======================================================================================
int Inserter::override_stack_size()
{
    return obj[N_override_stack_size].toDouble(0);
}
//---------------------------------------------------------------------------------------
void Inserter::clear_override_stack_size()
{
    obj.remove(N_override_stack_size);
}
//---------------------------------------------------------------------------------------
void Inserter::set_override_stack_size( int sz )
{
    obj[N_override_stack_size] = double( sz );
}
//=======================================================================================
Control_Behavior Inserter::control_behavior()
{
    return Control_Behavior{ obj[names::control_behavior] };
}
//=======================================================================================
void Inserter::control_behavior( Control_Behavior cc )
{
    obj[names::control_behavior] = cc.ref;
}
//=======================================================================================
