#ifndef PR_ASSEMBLE_TMPL_H
#define PR_ASSEMBLE_TMPL_H

#include "blueprint_book.h"
#include "item.h"

class PR_Assemble_tmpl
{
public:
    static BluePrint_Book S2_templates();


private:
    static BluePrint prepare( Item it );
    static QByteArray tmpl_repair_pack();
};

#endif // PR_ASSEMBLE_TMPL_H
