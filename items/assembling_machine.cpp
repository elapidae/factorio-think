#include "assembling_machine.h"

#include "qdeb.h"

Item Assembling_Machine::recipe() const
{
    auto r = obj.find("recipe")->toString();
    if ( r.isEmpty() ) return {};
    return Item::get( r );
}
