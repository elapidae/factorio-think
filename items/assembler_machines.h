#ifndef ASSEMBLER_MACHINES_H
#define ASSEMBLER_MACHINES_H

#include "item.h"


class Assembler_Machines
{
public:
    QJsonObject obj;

    void recipe( Item it );
};

#endif // ASSEMBLER_MACHINES_H
