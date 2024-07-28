#pragma once

#include "blueprint_io.h"
#include "item.h"
#include "control_behavior.h"

class Inserter
{
public:    
    static constexpr auto N_override_stack_size = "override_stack_size";

    static constexpr auto burner_inserter       = "burner-inserter";
    static constexpr auto inserter              = "inserter";
    static constexpr auto long_handed_inserter  = "long-handed-inserter";
    static constexpr auto fast_inserter         = "fast-inserter";
    static constexpr auto filter_inserter       = "filter-inserter";
    static constexpr auto stack_inserter        = "stack-inserter";
    static constexpr auto stack_filter_inserter = "stack-filter-inserter";

    static auto it_burner_inserter()       { return Item::get("burner-inserter"); }
    static auto it_inserter()              { return Item::get("inserter"); }
    static auto it_long_handed_inserter()  { return Item::get("long-handed-inserter"); }
    static auto it_fast_inserter()         { return Item::get("fast-inserter"); }
    static auto it_filter_inserter()       { return Item::get("filter-inserter"); }
    static auto it_stack_inserter()        { return Item::get("stack-inserter"); }
    static auto it_stack_filter_inserter() { return Item::get("stack-filter-inserter"); }

    QJsonObject obj;
    int pos = -1;

    Inserter( QJsonObject obj ) : obj( obj )
    {}

    int override_stack_size();
    void set_override_stack_size( int sz );
    void clear_override_stack_size();

    Control_Behavior control_behavior();
    void control_behavior( Control_Behavior cc );
};
