#pragma once

#include "blueprint_io.h"

class Inserter
{
public:    
    static constexpr auto N_override_stack_size = "override_stack_size";
    static constexpr auto burner_inserter = "burner-inserter";
    static bool is_inserter( QString name );

    QJsonObject obj;
    int pos = -1;

    //Inserter();
    Inserter( QJsonObject obj ) : obj( obj )
    {}

    int override_stack_size();
    void set_override_stack_size( int sz );
    void clear_override_stack_size();
};

