#ifndef ASSEMBLING_MACHINE_H
#define ASSEMBLING_MACHINE_H

#include "item.h"

//=======================================================================================
class Assembling_Machine
{
public:
    QJsonObject obj;

    Item recipe() const;

    static void set_recipe( QJsonValueRef ref, Item item );
    static void clear_recipe( QJsonValueRef ref );
};
//=======================================================================================

#endif // ASSEMBLING_MACHINE_H
