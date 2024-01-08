#ifndef PR_SCIENCE_BEFORE_ROCKET_H
#define PR_SCIENCE_BEFORE_ROCKET_H

#include <blueprint_book.h>


class PR_Science_Before_Rocket
{
public:
    PR_Science_Before_Rocket();

    static BluePrint_Book build();

private:
    static QByteArray tmpl();
};

#endif // PR_SCIENCE_BEFORE_ROCKET_H
