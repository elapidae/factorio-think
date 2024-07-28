#include "assembling_machine.h"

#include "qdeb.h"

//=======================================================================================
Item Assembling_Machine::recipe() const
{
    auto r = obj.find("recipe")->toString();
    if ( r.isEmpty() ) return {};
    return Item::get( r );
}
//=======================================================================================
void Assembling_Machine::set_recipe( QJsonValueRef ref, Item item )
{
    auto o = ref.toObject();
    o["recipe"] = item.name;
    ref = o;
}
/*
QJsonObject({
"entity_number":1,
"name":"assembling-machine-2",
"position":{"x":223.5,"y":136.5},
"recipe":"medium-electric-pole"
})
*/
//=======================================================================================
void Assembling_Machine::clear_recipe( QJsonValueRef ref )
{
    auto o = ref.toObject();
    o.remove("recipe");
    ref = o;
}
//=======================================================================================
