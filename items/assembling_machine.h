#ifndef ASSEMBLING_MACHINE_H
#define ASSEMBLING_MACHINE_H

#include "item.h"

class Assembling_Machine
{
public:
    QJsonObject obj;

    Item recipe() const;
};

#endif // ASSEMBLING_MACHINE_H
