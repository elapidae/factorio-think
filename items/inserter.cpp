#include "inserter.h"

#include "qdeb.h"


//=======================================================================================
//  Little blueprint for understanding how to do override stack size.
//static constexpr auto * burner_stack_size_1 =
//        R"(0eNp1UO1qhEAMfJf8Xst52Oot9EmOIqumd6G6K9koteK7N6vlKJT+y8dkZjIrNP2EI5MXsCtQG3wEe10h0s27Ps1kGREskOAABrwbUtdM7JEz8hFZkGEzQL7DT7D59mYAvZAQHlR7s9R+GhpF2vxfEgNjiHoXfNJVrury9GxgAZvlJy1VpCPG9kAUBtStcOjrBu9upsDprCVuJ5Jad92D6504Sv3np5lYJp08HB2IDGfkRe7kb+mxlIm4FNApNcPo2EkSg1fYdB8UzdRhraj2Q1W+8CeGPTP7K2IDio27qXOVF+XlXJYvRV6eq237BkBdhug=
//)";
//Inserter::Inserter()
//{
//    auto bp = BluePrint_IO::extract( burner_stack_size_1 );
//    qdeb << bp;
//}
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
