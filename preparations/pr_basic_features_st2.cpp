#include "pr_basic_features_st2.h"

#include <iostream>
#include "recipe.h"
#include "qdeb.h"

using namespace std;

//=======================================================================================
BluePrint_Book PR_Basic_Features_St2::templates_for_fabric()
{
    BluePrint _;
    BluePrint_Book res;

    //  need    war
    //  need    basic
    _ = Recipe::make_assemble_2( "radar", -12 ); res.add(_);
    _ = Recipe::make_assemble_2( "repair-pack", -12 ); res.add(_);
    _ = Recipe::make_assemble_2( "electric-mining-drill", -24 ); res.add(_);
    res.next_line();

    //  destroy war
    _ = Recipe::make_assemble_2( "piercing-rounds-magazine", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "firearm-magazine", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "gun-turret", -1 ); res.add(_);
    res.next_line();

    //  destroy basic
    _ = Recipe::make_assemble_2( "stone-furnace", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "boiler", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "steam-engine", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "steel-furnace", -1 ); res.add(_);
    res.next_line();


    //  need basic
    _ = Recipe::make_assemble_2( "pipe", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "pipe-to-ground", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "offshore-pump", -1 ); res.add(_); // from water
    _ = Recipe::make_assemble_2( "pump", -1 ); res.add(_); // engine for moving liquid
    _ = Recipe::make_assemble_2( "pumpjack", -1 ); res.add(_); // oil mining
    _ = Recipe::make_assemble_2( "engine-unit", -1 ); res.add(_); // motor
    _ = Recipe::make_assemble_2( "locomotive", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "chemical-plant", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "oil-refinery", -1 ); res.add(_);
    res.next_line();

    _ = Recipe::make_assemble_2( "assembling-machine-1", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "assembling-machine-2", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "assembling-machine-3", -1 ); res.add(_);
    res.next_line();

    // iron stick
    _ = Recipe::make_assemble_2( "iron-gear-wheel", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "iron-stick", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "train-stop", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "medium-electric-pole", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "big-electric-pole", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "rail", -1 ); res.add(_);
    res.next_line();

    _ = Recipe::make_assemble_2( "cargo-wagon", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "fluid-wagon", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "storage-tank", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "rail-chain-signal", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "rail-signal", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "landfill", -1 ); res.add(_);
    res.next_line();

    _ = Recipe::make_assemble_2( "solar-panel", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "laser-turret", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "accumulator", -1 ); res.add(_);
    _ = Recipe::make_assemble_2( "substation", -1 ); res.add(_); // hard
    _ = Recipe::make_assemble_2( "beacon", -1 ); res.add(_); // маяк, hard
    res.next_line();

    return res;
}
//=======================================================================================
BluePrint_Book PR_Basic_Features_St2::recipies_for_arch()
{
    auto raw_bp = BluePrint::do_import( raw_template_for_recipes() );
    auto rec = Recipe::extract_recipies( raw_bp );
    for (auto &&r: rec )
    {
        cout << "    _ = Recipe::make_assemble_2( \"" << r.name << "\", -1 ); res.add(_);\n";
    }
    //exit(00);
}
//=======================================================================================
QByteArray PR_Basic_Features_St2::raw_template_for_recipes()
{return R"(
0eNrVXe1uIzmSfBf/lhbFb9bg3uQwGMi22q1dWdLJ8uzNLfrdTx9uFy2TVRGhARr+M8DMWEFWkpkkk8HI/9zdr1+Xu/1qc7j77T93q4ft5uXut//+z93L6mmzWJ/+2+Gv3fLut7vVYfl8N7vbLJ5P/3bYLzYvu+3+ML9frg93P2Z3q83j8n/vfjM/ZpM/Xry8LJ/v16vN0/x58fB9tVnObQFhf/w+u1tuDqvDannpzPlf/vpj8/p8v9wf22h1Y3a3274cf7bdnNo+Qrl/hNndX3e/zfv8j3Bs4XG1Xz5c/n88dfQK2MLAlgN2MHDggD0M7DngAAMnDjjCwJEDTjBwzwFnGDhzwD0MbDoO2XQ4tCGhce8zpPsZ3P8M6YAG90BDuqDBfdCQTmhwLzSkGxrcDw3piAb3REO6osF90ZDOaHBvtKTLWNwbLenoFvdGyy6GxGpIeqPFvdGSLmNxb7Sko1vcGy3pMhb3Rks6usW90ZIuY3FvtKSjW9wbHekyDvdGRzq6I3am7A4S90ZHOrrDvdGR3uhwb3SkNzrcGx3pjQ73Rkd6o8O90ZHe6HBvdKQ3OtwbPemNHvdGT3qjx73Rk97ocW/0pDd63Bs96Y2eOC2y51DcGz3pjR73Rk96o8e90ZPe6HFv9KQ3etwbA+mNAffGQHpjwL0xkN4YcG8MpDcGInPDZlhwbwykNwbcGwPpjQH3xkB6Y8C9MZDeGHBvDKQ3BtwbI+mNEffGSHpjxL0xkt4YcW+MpDdG3Bsj6Y0R98ZIemMcvHG93TzNvy82j8vH+Wrzstwfjn8wklw+OuePGmIUEtUJ6msScusYciat4Cet0AvJb6ivqRPy9Rjy4Hcvu/XqUP3yIW4mANEKCXWsr4O3/Xu7fVxu5g/fly+j+fTGSCUvpNCxPgYh648hRyWFjkEnJfGPQWclhY5B90riH4LOHRkbzGRwyEbJymO9tcpdAgbtlKw8Bu2VuwQMOigJfww6Kgl/DDopWXkMOit3CRh0r2TlIei+U+4SMGijJPwxaKsk/DFop2TlMWiv3CVg0EHJymPQUblLwKATuQQUufnGEtBnJdGP9Va6nkjY1X2nZPpBbOmCAsS2Sq4fxJauKEBsr2T7QWzpkgLEjkq+H8SWrilA7PIg+LR6OaweLgeL+cthu188LUcvFeK5jf3yf16Pv/jj22p9DA4XkthPAtpwwDpsN8v5t9f9ZvFwAn3Yvp5Ybt2P36vd6pWLCOyTCTqOZ8NFwccBz9VuKnAagojj2TBBMHE8G94IKo5nwwTBxfFseCPIOJ4NEwQbx7PhjaDjeDZMEHwcz4Y3gpATWH8kGDmBjSMEJSewfklwcgLrlwQpJ7B+SbByAuuXBC0nsH5J8HIC65cEMSewfkkwcwLrlwQ1J7J+SXBzIuuXBDknsn5JsHMi65cEPSdOZtwMwciJrJcXlJzq64GRew/3tmN8WJ2fIuwXj4v9XbWNwSNfnhfr9Xy9eN5V8kzvyKFliMH9npePq9fn+XJ9/Lr9caO7266XY1cp4dzZzXL19P1++3re2ZqYZyb2M5NSdeNakHPY66XWBxSkHMzaoWnt5W6x2s93i4d/VW3ujXwr1Oz84IzfFsdTRRsrTWM50hC5ZYjdarl/OP14fzyFPL4cMZ4W/3cEqVtl8Mt27/vp3gey96bpNd+O/rnYP090O7Jp/GlfKig6mC+ZCWc6OZKZmRyrzuTZW0oDeFPPDkPTnZ5eN/PD636/PFQHoKDvjEawMNnnYPQbmSamJe1QpM6u7PA+B55XmxPI4361XtdN4vS8YvNDPBvfx+dkCDPTu+p8LJg8YFP9eFN+ZkJfb4pdYoumrobnfrtaL+uLbEHywVrxzZj0clgujvbYPLXiUch6aqQ59j05IEWiwTfGPvnqgER2FS5yA59Wn13dRAUPaCxi+GnvLmg/oLGnl9/ILr+hG7PA/LCdP53X37otPPsF00swzf0pvqCJGZV9dhMtKWi+hcZufa8H7KN3uFz3DNYJzXgzx01Gq6mCCjSxmyzasNdnGluFNuxXpKsWPn9FjjNr6ktJQRQamdKe/QiH2qfIAFrsGSG7zPo8OsqNdS9Jx1bXcIAkOadtoSX5JGlwd0r8jcywKHfndh62m81lMF9Of2FO/3jaL5eb8v3+6vHUWP/j9+O33t0vLi/5oaucy6F96gqnYCghp1/zs+eH/Xb9x/3y++LP1XZ/+rOH1f7hdXX44/j/Ht9/ezwCHbv5Sdrgz9X+8Hr8L8M6ev6L+fLP5f6vw3Gherq7tPJyWJz6frpbedg+7xb7xeHU2t1/3f3gDJhPBqw+ju34mzV5HLO5jCM2fkUaYGoUC+YWkgb4NaN4OmndNIq5a46ikL8w1wHVV5GHWH3cAy33l73QpKzDZWa8GWr7eti91k+f2dPTL+vTLxDTr5l8mZyLAZiL+RfPxdzdPBl9czJGPf1iGnuUZOq2TvT0MTeEr0zMnyLtMjljMjBjzNcPX6k5Y9hs18CAzP3HM9t6cTTgWL6rZ0/IA7nwuq2X1/ujbc5/Wm3J0JOzSCSxk7O3xOSs58Km5mmPnAaKT/ii87Q3rXlakDvpJJ6pZ9asqSdyen5h9EmfPNzKuJteBXtkFfTpy8+V5irYR3oAizwOPYCJHMAirzU5lAkYyqLvv+iMdPtYxuZYZuWA3jUO6AQROH5c9Ks6QZ2yQc+53KCvNo39uS3Iv2CC/z2fnNPH1XLx8PD6/Lo+D061KSuY5fwdVTTl2ed5ga+ieV7aLscWmKCTdzZmFYy9gRn2kTle3cAsF0dnOf7ipLx4dpaX3XL5OH/ePr6ul3N3yuZVuzDEh/32fnv6nBpH663RxmewOeCBb/M2zz6srNZW83a2U1yvOZAERbdAa40kIZI3TAvfArMCWGiBOTnpnGv3V8nMXP3+yhr9mrTa1HHH5nKjqSAQ3t4amciaWIKcW2AHDDsJZLrP2HVluCyQ6VBsRfQAtHdBzm0/kS5CBiRlp8gdgLYoSLnTi/ZA0augA0k2a5kc3qBUMNZae8dgFX5gM45Z5aKlGcgIbu4QwWwLLAlgrgXGrn8DDzy76vo387ZKV7KWvQgNabypPDst376x5BL83CIUOsjtC37u9MQu0D/dJXpgYjOE3W6kqSq2U7BBI3nG++2NRgpK0AQ/JGpB00lB0ykch2awcMoJshktCG29wXcbx1FLqOkNYK3TqGc8cqBy5k4aI2+11ozWmhMkOCptVbG9gt1h2AE4n5mf57OuPq6M7w0yE2Pj2g4iBX+XasxIjWVB4wId1V7BxkaVkN0bBDTAfhO6e4OCBoptFWzQJk6xCYjtBekPFDsI2h+ovaPSbxA7Kf0GbZIFZRG034ogCohNCPAV2JhNoqLcjmIrmiioTRTtdhTbK9igTYJiExBbkW9HbZIEpRgUOyvYoE16xSYYNqHPZ9n1MhlB4wbFtgo2aBOn2ATE9oKSDmqTIEjpoNhRwQZtkhSbgNhZkABCbdILEkAgdu4UbMwmhKCfY9fLrEgXoTZRpItQbK9ggzYJik1AbKXAAmqTJEguodhZwQZt0is2wbAJZT/HrpeEtJ9j10tC28+x6yUh7ufY9ZJQ9/PseknI+3l2vST0/Ty7XvZJsQmInQVNKdQmvaCFhWE7QurPk+ulI6T+vGOxraCFhdpEqX+CYiv6YKhNFH0wFFspgYLaJAnaYyh2VrBBm/SKTTBsRq+PXC8dQQ3ymcW2CjZoE6fYBMT2gmYaapMgaL2h2FHBBm2SFJuA2FnQekNt0gsadSA2o9vHrpeMbh+7XjK6fex6aZUKRSi2otuH2kTR7UOxFd0+1CZJwQb7nRkOTLrtxt0V5CGqNenG3RXcoZ9E//nD9vl+tTmzyMcoPrUGa08SyocSEyXoLzSp7eb0kOPykOHyAuH8dsIU1ex//1H9GCN/TPf3f8zq+CHz3XpxWDY+YjYJ8bDd7Zb7ERDbsgRD2wj9TWQC55zWmJEa8wqPC3N0hlrFLu5E9dLIbngYIhW7ADO0KnYBdtJbgQbLynnprYBpoQlvBVJugQlvBVLfAmO10wY6UxuTFVkyQD/pAmtmGpPVMhwupNuYbI2L4RKwjZllfbs2JqsoOlwANCdmQXEawcnTOAYsSuambRdoybLp+U3rDRaYzW+mhcmm52IIOmazn1GWgGtjIg9W/cd5M0k/dgUhaXwWeWAW9bLEW/OrI1sQbTiStjE1gn3FosDmKVqtsb7d2MjZgqkLasmpUnCSRp4j+YlJUrCPGOK+ag9FhKw9cYTHMSm2wLIAllpgPaRe2U8CFYQi7B1N/+FDr57RNB5EusQ+wB5o7unqfe/227eX79v9cr57PX5xtTErPya+bqzdhsP0huP0ALBvRQvM6gh0Jx3EmatrprtEK2PnlnEu+rPz182q7osFB2nMRgNft20jVgywwKzP0pnLpm6fzArr2JZ91tuH7fP2sPpzWTcPLRcUWi0dl/Dn1cNifcpibOqDkTGBbDsdejIr3mnT+GCk1uNml1lPtn0zbKzW8/3y2/F3+7/qBmIVd50dixr/bOj+u0y/Dfej5jsOx+m9uct1f89Blr749FkNKWWXdf3s6zaqv6+2yYYEb8bN6GfehroJ2ZAwsAqAzzP1z+tlBezrNu9XT1e2qTXYd7ya7VtLE0K5TlAQK9pIRNm7c2C7ngejskCut7LQdgofDX1ORp++ru74PbZl8NN7toJkNTFWwbbHqpou7NlwEZp7p6pbVttkw0doho+Xw3K5fi98WG1MyeN+Nl71wMQILNmrCT6JreRxW2cR3yl53NZ89J2Sx/UtMCWPG1pgDtGkNB869fWEkb23Dc0v33k9kQ2JlviOTacNOqloC5ESFv2yg5iag5j0mwPQxJB2a7xa+SYWft/1+u0E1m+D5NZt1+53rKIiOtzFue+LTrjQUgr0xupXQODAIYG5OPD+GhPb7lYT900Te/1GDDQxol1aHJi/6CyOvmniqF8QgiZGrmjclw8UqWuaOENnmiKF0dqpmRtuXltbScveJTnWxyxUsaH7xRPgVk1Zn5phzEKldQy5cbD0VXJgBw6pM1nkVL7owOXmEm+DXGIohVr+LJ2k2mbRVNOQ3rLVFIrMRaW5U/dPkm3e9rNobb3JpN8kg5MI2TUH/9UnUd88mNwgwlcb1Te9v+OIVhOx3nXa1bpXrpK9Q2J7+NX7p1Mgu2V0Q+dao1sQXEfu/y3lMo6N7JHNRzDkVdtel+rYio5nc3viJK5CawPlkqKgnhxW4sgzHNV3cKjanVd0AEFojyjqDoHCIZB4srNne2v5OkDmaiTxsH5xfPBq5SPrYuJSxUsag6iRCI1Bw2Lj/j1Uv0axcW8vMqQg9i0FpPiJE5kqHdB8IdQLPWsbQr0wkNiMeiEbFRn1QjYsSuqFKLaiXohiK+qFKLaiXohi81V0ivQy65+GqU9ZkJSmvJTRSWQjGKOTyEbeDzRl0PpBtz6zrF4Rt6ZGgFFlZOMko8rIxklGlZGNk4wqIxsnI1++rEio0zOHKV/2gc82OW+CftkAqZp7RgeSXVEYHUh2RSFI2Y5dUQgdSMeuKIkveOxuWFESueP7J1Du2BN6k46N+YTepGPXqqTo2qHYXtCeQ7GDoOGGYiu6dih2EvTKUOws6Kyh2Py+o7gqYn3UMru+Bs9u3F8JjUvPxkpC49KzsZLQuPRsnCE0Lj0bZ7Ki2YViK5pdKDZ/2ilu2uh574l5/5kLPTnpE6d34dPnL7lF4aLG3v7Z5bk58TjHBTt8VpTI0JFWlMhA7F5RIkOxFSUyFNsK6lUJKrDke0oFZCwGIyl/gmb+MQtdBQuCyBRqcqasS7CIWZrve33P51qDnmu1mYhujTvY8QBXkNYxQZ/w9wa4xjMBKsYV5Pj2NU/RcTs9qQJBkQ/k6hsIwnyILDYRfxKL7fi5r+dDHLOj/fjyY2LSh85rTAInKAIEQh819OyIKCVaUWzmRjmaG42UdWIAlKIKTNVk8ogRmBrKHYttBHUoFNsqZAnM3kaSpgD7rZRnTY2yhsFItA7XQpMueg1CjAyENGpxmQliS5ewILZSQg7EttIlLIhtlMtMEFu6hAWxnXKZCWJLl7AgdlCuGEHsqFwxgthJuTwDsbNy6Qdi0y+0Bu9saAQGolSyZX3dGeUiEcS2yjUTiO2U6zEQWylRhWIrJapQ7Bue5zTnXlKufcD+ZuW6CsTulWsfDJvQ7HRs/PCGHUM/OYaEkKdj4wdBTHRs/CCIiY6NHwQx0bHxg9b7LFpojqFS8gbtb1auoUDsXrnOwbCDUvIGxTbKdQ6IbWFlmI/O/Sueutz41iX0LSWFEJTqPKiJvXJH00HHcILX6EdCXh2bSbz71O65BTJEgUlHFVdCI421Lz9CYPNRfjoqhl67vpHMRXAFgyHnFMEVDIacU5x+6kigjIiRHHJxUET6T01cktLnBPR2c0o8X+bUH7v9Md4d2zrNn+W3RuteKARSmQ1VbEZ2NfgbvSVGrTWpoEYgCIEhsXbLytUMiE35f7xtahOVosPINrqafiWYeyGTRiKYe6FnsZ3Sb9AmXuk3iK0UzUBtohTNQLGTgg3aJCs2AbF75eoCwyZYdNGx2NJVUWu7QvDm4vSxnmDKxY8LRBXNszLG7wtozFeaga/3x+PD+U+rLbGKiEPiMaarlrbrxX6+W2yW63pTtI5q12rqYbF/2s7/vXhqfVVim3Ktpr6tX1ePY02x8qlDVueTAS8sg/nxtPevelu0bKpptbVfrNbzh++L1Wb+di6tNdjzPPwhcRAvGvf3i/1FagokOhz3mfP7/WqaYR96VnZ9OLlWzTFmCP7tctFYz1FDQrAUNYSwGMOwG87LUSkVEXrl2B976BhFC7kO59froT/27eQEh+2u/hVROAzGjH2FUgoUtVCG6Y0fPbYK1su6uTVPqxk6dpiE+3Amjo26FrFj0/bD8bNlgdgp+3ZsGsRO2bd/xrZVbI0KFqX6JJHggg07YtRKUdgRf8aOVWyNC6ZaSSmI156ZvYLW8h2jSCe30YyC1vrSgs4Flma4Dvof9Jii8bPoqoJeERLwHO4qIyQVHw1dHCGMf4CdRRPqH8AKoA2Xdk1bmYatorapiJLzGLoyQhz7sJPU2slYDZm1aPBltGNnQ6+s/pBWe7RKejwmDNvw+vwR0ueP1so6evXBPUv2tRTXohUI3+nqk/A9+tTuPFr8RUok5xqthxhGveY0UGdxQmfqXxKV3RI4tZOCDU5tJesWG2UIou2V3RBmBadQskErOLYEUrTjk6XufQ6+eY9sHCEIafFj5qeK5hW01qyQVPbaaIrKXvtL0+hb0k9czze46s4kHwchp64+9JlXHhkCkufSKdH1TDqlyGJOBeyC1zbCKR06Hr4mbeQ4XA3aSPSdzLCNkOBlpDl4RQsBa4HP7RWZaXYyekYGp8xzT01Guqj3QDhFh8LrLYBDgYj6F8b/NQ5lbnSnZj2b6HltgeLmgp6KjO5NeQ8yORWhwgHuqw9jbA5jlnnDqCv2eguYKwZBginJUzG8PYY9XxYZ/FQ13JdNzcmA6F279Kvn5I3FLI7D1pqUwcpEaHBSBrquQcdOSq+3AH5D4C/6jD7tGa3Zz1e2k3M+UuUrftn+9NY5H5pzni2S4B07X2girWVb6PVvwLwqdvo3gC2YW67PWa+KlvUq0J8iVA7Gf3V/iqblT9FJjPjPMx2geMco8Qc8lA+NyrMBdLLHGwoC85Od2cQXXIfJuY7s4Yt+f9H9Umxu4iMd2XsyssdebwGbiokqKWMQfx25mksGY3B83JNVkahXEu62OMPQpi0ZZxJFvwi3DkC4QbyLjjyJ3bxOxpyCrD11AfarF1nT3ZxVTc1ta2LoKOHGZTYpT0LQ6Q8pl/VU1CQY5oGNlwzD/OOxqYpmNVaR5vwMA509FRNarZE90xNarXHk3FG9B8xRwW6tSpliiV2vSsAISryw5uzrlZvB1rf3Ei+s1beCuT1tyeFTJaHPSEiW2pGmqtCE4MI7tMOgqZ0DYqL2EsCol7KfgXugZ6FpJtiVlT5cWWdfZyn0mS/fhs6eni86h0EnQt4zcmZPhLpnYqEtX3wONQjuqZmF9gI0aJAgGASEjkKhOdQiSSiQh2JnBRu0Sa/YBMMmiNXGkTYhaNbGsthWwQZt4hSbgNhe0JJEbRIELUkUOyrYoE0UfU0UOwsamKhNekEDE8SW9DVBm1ilyCGKbQXtTtQmTtDuRLG9gg3aJCg2AbGjoDmK2iQJmqModlawQZv0ik0wbEZnk10vGZ1Ndr1kdDbZ9ZLR2WTXS4LkbNn1kqA8W3a9JAjQll0vnaJ7i2JnQesVtUkvaNSC2ITepmXXS6L4uGXXS6/o36I2UfRvUWyvYIM2CYpNQOwo6PaiNkmCbi+KrZTMRG2ilMwEsQn9Tceul0EpZYliWwUbtIlTbAJiK6UsUZsEQdMYxY4KNmiTpNgExM6CbjJqk17QTQaxCaFKx66XhFClY9dLoqi1Y9dLoqi1Y9dLgjXm2PWSYI05dr0kSkx7dr0kFCU9u15GRa8atUmv2ATDJgQkPbteEgKSnl0vk1LuFbWJUu4VxfaChjdqkyCIV6PYUcEGbZIUm4DYSmFU1Ca9go31mynDzK5pTBlmdg/BlGFm10umDDO7XjJlmNn1kinDzK6XWdJlA21CSEyw6yVB8gnsepklRRkMmyAABXa9JAoWB3a9ZAoWs+slQf8J7HpZ8H+Qoq/RIphBKPqK2jkq2KAtkqAkj2JnQUgctUmvUGsh7NwpAuiYTbJUwBfFtpogocT9y5q0IvgliiR6hEqhZ6mobnQYdtRoyQq1MHeKRjpqpKxgg0aSVBUx12U0Fi2LLSkuNkrHZqNopEfXQiNoBe9gUImhzLB93qG7Vj8D+gzFtrtZH53II3cYMqt47q8aeBfoXS82j99W66pIby5YPiNyXWzfe/rZUvrUe+AN0vuXTbxDyraT6r18/lxE0TJbo7VmBFHubCUdY6geRiZoQwU2VDcpW+kFCthvpf5I7LB+U4ttd+PgJuDMcEqQvzdRRclK0G8FU8tUBXq3buixNzO5oAmhETX0UFRyRo9Kb038vVHJWSb2ol/pWE3l991OyBWtR5dm2flZ9qn+DbQCshlrbkRjMBeko5/PNucP2+f71eb8XnPk9F8xXf2BaTmun16Urg7L57uiC7vdcj/frReH5eUl6WWoZ+8T4vyYtvIZUXoKXf2GyQBCEJ6GhQidaRkJTubDYE9FV9dLR5nQK9HVd1IoD5JIfPZGemz4ZjgA32r4HwLziLGUekihoSOfCRJU/Dgvq2hBfTgWYiXk9ceQ52M1BhUkKKyl4clKralTz1uR1bOv4QY2e72peFJwrTc1ePJ+e789DUaNHPUTvD4GvRyd098fnV8Oy+VaCM6h04JzUoIzwcIasqCVpqrYVgn8ILYTMpUBksHOBAurwAb7HYQsKIodpSzoZ6tAWdCgSKajX5KFDCuK3QsHs8/Y1UNf7LStg1S1IhNMrWLngFkpiit5EtRCMkHdipYdEubJe4EelWhKcLkKm0VsRKhDf0BGZGxuJWVz1BCUz1E5/YfUQtNO/wHbZBYcLkCu/nS4uaA3Tq3VzQ5TDDhdfcDU6kVwuaJhsR2RCzpj/vh9dtkWHa25fl3u9qvNqSN/HvdQl8mYjU+9Tdk6cypR+OP/Ac/pROg=
)";}
