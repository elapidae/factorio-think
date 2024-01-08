#ifndef PR_BASIC_FEATURES_ST2_H
#define PR_BASIC_FEATURES_ST2_H

#include "blueprint_book.h"

class PR_Basic_Features_St2
{
public:
    static BluePrint_Book templates_for_fabric();

    static BluePrint_Book recipies_for_arch();



private:
    static QByteArray raw_template_for_recipes();
};

#endif // PR_BASIC_FEATURES_ST2_H
