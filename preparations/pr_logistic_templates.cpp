#include "pr_logistic_templates.h"

#include "blueprint.h"
#include "recipe.h"
#include "qdeb.h"
#include "blueprint_book.h"

//=======================================================================================
static auto tmpl = R"(0eNqVlN1uhCAQhd+Fa9lUXRV9lWbToE50Uv4C2O1m47sXbdI0rZhwBwTmm3NmmCfpxQLGovKkexIctHKke30Sh5PiYjvzDwOkI+hBkowoLrcddw5kL1BNVPJhRgW0IGtGUI3wSbp8vWUElEeP8B1v3zze1CJ7sOHCeaSMGO3CY622DELAurhUGXmEh9fmUgWQhQH3vCyM9I4WAv0fpUilVDHKZAFUlFP+cCSMuEgKAgZvcaBGCzjgNH84CnCae73Yzaz6doC4pkppY1KMvoOl7o5+mI/EVImkJlqarZk8V54OWvaouNf2CFgnutdcz9wrs/bIvyZVVR1TxS36WYIP+Z3rYqnIaMnGsBhD0c55baKPLE/uwvwlURMr481hzCaJ9+LwT+WpI4JFK+YkF4IKLs0hKHVKsPjXsnqyXMpNE3UG+HsAbKNwH57dr1mbkQ+wbo9ZsBCnLZqGlaws63X9AlZU1No=)";

//=======================================================================================


//=======================================================================================
BluePrint_Book PR_Logistic_Templates::build()
{
    auto tmp = BluePrint::do_import( tmpl );
    auto recipies = Recipe::extract_recipies( tmp );

    BluePrint_Book res;
    for ( auto r: recipies ) {
        r.prefer_assemble_count( 12 );
        auto cur = Recipe::form_in_assembling_machine_2( r );
        res.add( cur );
    }
    return res;
}
//=======================================================================================
