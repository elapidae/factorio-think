#include "prototypes.h"

#include "vlog.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

#include <QDebug>
#define qdeb qDebug() << __func__ << __LINE__

//=======================================================================================
static QByteArray read()
{
    QFile fin("../factorio-think/prototypes.json");
    if ( !fin.open(QIODevice::ReadOnly) ) throw verror;
    return fin.readAll();
}
//=======================================================================================
Prototypes::Prototypes()
{
    auto obj = QJsonDocument::fromJson( read() ).object();

    //qdeb << obj["application"]; == factorio
    //qdeb << obj["stage"]; == prototype
    api_version = obj["api_version"].toDouble();
    application_version = obj["application_version"].toString();
    prototypes = obj["prototypes"].toArray();
    types = obj["types"].toArray();

    for ( auto t: prototypes )
    {
        auto o = t.toObject();
        qdeb << o.keys();
        qdeb << o["name"];
        qdeb << o;
        return;
    }
}
//=======================================================================================
