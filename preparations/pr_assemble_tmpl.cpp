#include "pr_assemble_tmpl.h"

#include "qdeb.h"

//=======================================================================================
struct AssembleTmpl
{
    AssembleTmpl( BluePrint tmpl );

    BluePrint tmpl;
    Item src;
    int assemble   = -1;
    int const_comb = -1;
};
//=======================================================================================


//=======================================================================================
Blueprint_Book PR_Assemble_tmpl::S2_templates()
{
    static auto list = []
    {
        return QStringList()
                << "repair-pack"
                << "radar"
        ;// it is ok
    }();
    Blueprint_Book res;
    for ( auto && l: list )
    {
        res.add( prepare(Item::get(l)) );
    }
    return res;
}
//=======================================================================================
BluePrint PR_Assemble_tmpl::prepare( Item it )
{
    (void)it;
    auto tmpl = AssembleTmpl( BluePrint::do_import(tmpl_repair_pack()) );
    auto res = tmpl;

    return res.tmpl;
}
//=======================================================================================
AssembleTmpl::AssembleTmpl( BluePrint tmpl_ )
    : tmpl( tmpl_ )
{
    qdeb << tmpl_.build();
    exit(0);
}
//=======================================================================================
QByteArray PR_Assemble_tmpl::tmpl_repair_pack()
{
return R"(
0eNrdlt2OmzAQhd9lrvGKnxBY1DepVsiYWTIqGGqbqFHEu3cMWkRJFK2UXuUGZbB9zpwPg3OFqh1xMKQdFFcg1WsLxc8rWGq0bP09dxkQCiCHHQSgZecraS12VUu6EZ1UJ9IoYpgCIF3jHyii6SMA1I4c4aI3F5dSj12FhiesSm3PGifJ62pB2qJxPB7A0Fte3GvfAQuKNHxLA7jwryh/S9mJO3Wmb8sKT/JMvfETFRk1kit5rF5Xf5KxrrzJcybjRr6zNrLMEFJfHOdpYPGwTno0oS+6QRrpvBX8gGkZ16i8kfXKkb80BlFvI1MNRT59TLzgBkP8BIbsdTAkj/fVLYbD+4ohnTEYVDTnMThIMmKQ6hfccTo8ATyZnWoyS9ZZ7CXwp09AiV8VynF1fwBisw+T13kds9X9y0qwTUV6trlDId9th3sUPqllht86XP59h1lt9GFFFIbbA+Z/JM03O78h60gJdULrhOWkssHHj3wN+70msk0Dvj7u6nRXH3Z1vKs9g/nT93vklsst4C9Kd5GuREMW4HN6hl9s/ggEcGahOXOcR4fsPc6yPMmT5DhNfwFZesq/
)";
}
//=======================================================================================
