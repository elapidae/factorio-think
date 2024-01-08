#include "pr_chests.h"

#include "recipe.h"
#include "qdeb.h"

//=======================================================================================
BluePrint_Book PR_Chests::tmpl()
{
    auto chests = Recipe::extract_recipies( BluePrint::do_import(_tmpl()) );
    BluePrint_Book res;
    for ( auto && it: chests )
    {
        if (it.name == "steel-chest")                     it.prefer_assemble_count( 12 );
        if (it.name == "logistic-chest-storage")          it.prefer_assemble_count(  2 );
        if (it.name == "logistic-chest-passive-provider") it.prefer_assemble_count(  2 );
        if (it.name == "logistic-chest-active-provider")  it.prefer_assemble_count(  1 );
        if (it.name == "logistic-chest-buffer")           it.prefer_assemble_count(  2 );
        if (it.name == "logistic-chest-requester")        it.prefer_assemble_count(  2 );
        auto bp = Recipe::form_in_assembling_machine_2( it );
        res.add( bp );
        //qdeb << it.name;
    }
    return res;
}
//=======================================================================================
QByteArray PR_Chests::_tmpl()
{ return R"(
0eNrdWO2OmzAQfBf/hhM2n4n6JlUUAdkQS2CobaJGJ969NjSBIybBuWul9k8IjplZ7+6MTd5RVrbQcMok2r4jmtdMoO33dyRowdJSj8lLA2iLqIQKOYillb5LhYAqKykr3CrNT5SBS1DnIMoO8BNtcbdzEDBJJYUBr7+57FlbZcDVhBsSZQK4VGMOamqhHqiZZtUgHnkLHXRR33zvLew65w6GPA7IAOnfIBW4CphDTvv1CQlQuvkJhEQGJv/GJKq0LN0yrRoTfvQs5MA65Hgp5LIuqJA0H6J2hax5WoAp+tCWFOOVpI0CpGdwG16f6UFxGdgja/ZgJXuay2fksTX52nxn7fFo5kxsOYm3kpPDj1ZdzbSbG20FB9pWLpSQS64ebuoSTK0VzmgZ0OKU1S3XosV4ZyDB3irpjsh+j3ygaknDjMiEiq1j38xiV9bFBgqh52D9UXAANvUfelCmQbpdN1/sxrjW0V9aZWy84LW6uhmU8rFdhfM1K6Crj7KmNToM9i09MTAbDA5W4fgfcPr0SV6X+wxO6ZnWXE/MKc9bKvfqt8Pt6SPlQu7v9ocz5bJVI6NP9jPclF2k6vsCDRxCpnqr8fRN1aQ8lZoKfUOdTQlxqEtoWvzodAvu+DAVoV0n4WASQj8QD631W6b7Iy1V+ocd8Lo1jgma7DiatO0T0xkbMbJqxHBNI9atXOrE0TOvFXNVtTLK+moZCIP7DN410zQXT04XH/fia2pcLcfxgPE1/ZJYJTb6nMI3q5QZ/8vKJN5Cpon3gjLjl5W5mSmT4PkAsZDqYsQPVUumAOoEcEoV7sF9VPtoVvtJgwX/TScQW3tJvtZeFs/NN6eJXjUatejZjoCXsuDbOA/2PmfpJLBX3+QdwFJ9JJqLLXldbHdvGM9UF65x2UlC75VmQo1WoeK/5N1wBm7SLP6kZoOlbo1trQwTywQnlq6AyR91BcOL7XgQedkehvzunIF7O/n3xUGqpGIQdIKDeEPiOPET34+67hfx3uVg
)";}
//=======================================================================================
