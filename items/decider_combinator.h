#ifndef DECIDER_COMBINATOR_H
#define DECIDER_COMBINATOR_H

#include "item.h"
#include "names.h"
#include "qdeb.h"

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

    void output_signal( Item item );
    QString output_signal_name() const;

    bool copy_count_from_input() const;

    int constant() const;
    void constant( int val );
};
//=======================================================================================
class Decider_Combinator2
{
public:
    Decider_Combinator2( QJsonValueRef ref ) : ref(ref) {}

    void replace_first_signal_count( const Item& src, const Item& dst, int count  = -1 )
    {
        Decider_Combinator dc{ ref.toObject() };
        if ( dc.first_signal_name() != src.name ) return;
        dc.first_signal( dst );
        if ( count >= 0 ) dc.constant( count );
        ref = dc.obj;
    }

    void first_signal( Item target )
    {
        Decider_Combinator dc{ ref.toObject() };
        dc.first_signal( target );
        ref = dc.obj;
    }

    QString output_signal_name() const
    {
        return Decider_Combinator{ref.toObject()}.output_signal_name();
    }
    bool copy_count_from_input() const
    {
        return Decider_Combinator{ref.toObject()}.copy_count_from_input();
    }
    bool is_train_stop_controller() const
    {
        Decider_Combinator dc{ref.toObject()};
        return dc.output_signal_name() == "train-stop"
           && !dc.copy_count_from_input();
    }
    QString first_signal_name() const
    {
        return Decider_Combinator{ref.toObject()}.first_signal_name();
    }

    // Filter is when input signal repeat to output.
    // Is used in power logic for not join counts.
    bool correct_if_filter( const Item& from, const Item& to )
    {
        Decider_Combinator dc{ ref.toObject() };
        if ( !dc.copy_count_from_input()          ) return false;
        if ( dc.first_signal_name() != from.name  ) return false;
        if ( dc.output_signal_name() != from.name ) return false;

        dc.first_signal( to );
        dc.output_signal( to );
        ref = dc.obj;
        return true;
    }

private:
    QJsonValueRef ref;
};
//=======================================================================================
/*
"control_behavior":
{
    "decider_conditions":
    {
        "comparator":"<","constant":2400,
        "copy_count_from_input":false,
        "first_signal":{"name":"copper-ore","type":"item"},
        "output_signal":{"name":"train-stop","type":"item"}
    }
},

*/

#endif // DECIDER_COMBINATOR_H
