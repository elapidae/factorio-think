#include "calc_lazy_bastard.h"

#include "vlog.h"


Calc_Lazy_Bastard::Calc_Lazy_Bastard()
{
    auto cnt = 14;  //auto stream_engine = Item::get("stream-engine");
    cnt += 6;       //auto boiler = Item::get("boiler");
    cnt += 2;       //auto pole = Item::get("small-electric-pole");
    cnt += 8;       //auto offshore_pump = Item::get("offshore-pump");
    cnt += 40;      //auto lab = Item::get("lab");
    cnt += 2 * 10;  //auto science = Item::get("automation-scince-pack");
    cnt += 14;      //auto assemble_machine
    vdeb << "CNT:" << cnt;
    exit(0);
}
