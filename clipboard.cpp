#include "clipboard.h"

#include <QFile>
#include "vlog.h"

//=======================================================================================
void clipboard::put( QByteArray data )
{
    {
        QFile f("clipboard.txt");
        if ( !f.open(QIODevice::WriteOnly) ) throw verror;
        f.write( data );
    }
    system("cat clipboard.txt | xclip -selection clipboard");
    return;
}
//=======================================================================================
