#include "mining.h"

static auto six_L1_drills_bp = R"(0eNqtVduOgjAU/JfzXAwtN+FXNmaDUk2TXkhpzRLDv2+RLBhFZYtPpM3pzJk5Fy6w55bWmkkDxQXYQckGiq8LNOwkS97fmbamUAAzVAACWYr+RDk9GM0OgWCSyVNQacY5dAiYrOgPFLhD7zGORwfCzsy0gVCV5fQGgKwFiGYBzkwb625GjCEiwDcv426HgErDDKODGddD+y2t2FPtxL2xAUGtGvdayZ7ZIeZhtkkQtFAEcYQ3ieOqmO5z70MIuupq+uAZSc6KXspdDmTMwehSNrXSJthTbubI84mc3JPHM9jRv/Vh/EJf6qMv9tMXLtGX+GHjJdjpmt4g24/0RjbmYF1H65NW7rtA4SO9q8Lf5MnaGpgh23qZSfIlZuZrGvFRjVcj4nBVRZOPVBRPK6cRJecBL0X9xuHUMc9BTZtD0IpZEYyyauUSeA2aPQFdtTIeTfKrlN/OIPGSVsSJ71Alz4dKWXOdqt0g191Mf2MEZ6qboWW2OM5ykm3TPIzCuOt+ASUYiB0=)";

static auto six_L2_drills_bp = R"(0eNqtVetugyAUfpfzGxfvl77K0iy20uYkXAxCM9P47oOa2a3Vzqm/FALf7cDhCgdmaK1QaNhdAY9SNLB7v0KDZ1EyN6fbmsIOUFMOBETJ3YgyetQKjx5HgeLsVQoZg44Aiop+wi7oyN8Yp5MFwQvq1uOyMox64Q+IcD1ENApxQaWNnRlQ+hW/dsbdngAVGjXSPpDboP0Qhh+osgb/iIJALRu7WwrH7OzkwVtCoLWqCvtnqSpUTrxbEZKbscatHfVk03BeHkSEgwitStHUUmnvQJkeY48Gdv+RPR6BjhZBB3Og4/9Hl0wzpMuiS9bUL96ofumikMM5IWeLoKM50Pma+sUb1a8YRHBaoeHeoKWWjL52adWMQQb+gGlsF1BnJe13RmpPnuwJ/25XojYaxshWNZBsowMYhAstZ9OWpdFTnu9NpeElYx4ref2aJ50o1aoekm10BoNk0SXLny/Zvhdgge7PMYELVU1f3TyIsyLM8rTwIz/uui+zxIiO)";
//=======================================================================================
BluePrint Mining::six_L1_drills()
{
    return BluePrint::do_import( six_L1_drills_bp );
}
//=======================================================================================
BluePrint Mining::six_L2_drills()
{
    return BluePrint::do_import( six_L2_drills_bp );
}
//=======================================================================================
