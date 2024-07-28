#include "blueprint_io.h"

#include <QProcess>
#include <QFile>
#include <QJsonParseError>
#include "vlog.h"
#include "vtime_meter.h"

//=======================================================================================
QJsonObject BluePrint_IO::extract( QByteArray _code )
{
    vtime_meter tm;
    QString str = _code;
    QByteArray arr;
    for ( auto ch: str )
    {
        if ( ch.isSpace() ) continue;
        arr.push_back( ch.toLatin1() );
    }

    if ( arr.at(0) != '0' ) throw verror;
    arr.remove(0,1);

    if ( !arr.fromBase64Encoding(arr) ) throw verror;

    QProcess proc;
    QObject::connect( &proc, &QProcess::stateChanged,
    [](QProcess::ProcessState)
    {
        //vdeb << state;
    });

    QObject::connect( &proc, &QProcess::errorOccurred,
    [&](QProcess::ProcessError error)
    {
        vdeb << "err" << error;
        throw verror;
    });
    QByteArray doc;
    QObject::connect( &proc, &QProcess::readyReadStandardOutput,
    [&]
    {
        doc += proc.readAllStandardOutput();
    });
    QString cmd = "echo \"" + arr + "\"|base64 -d|zlib-flate -uncompress";
    //vdeb << cmd;
    proc.start( "bash", QStringList{"-c",cmd} );
    proc.waitForFinished();
    //vdeb << doc;

    QJsonParseError error { 0, QJsonParseError::NoError };
    auto json = QJsonDocument::fromJson( doc, &error );
    if ( error.error != QJsonParseError::NoError ) throw verror << error.errorString();

    return json.object();
}

//=======================================================================================
QByteArray BluePrint_IO::pack( QJsonObject obj )
{
    QProcess proc;
    QObject::connect( &proc, &QProcess::stateChanged,
    [](QProcess::ProcessState)
    {
        //vdeb << state;
    });

    QObject::connect( &proc, &QProcess::errorOccurred,
    [&](QProcess::ProcessError error)
    {
        throw verror << "err: " << error;
    });
    QByteArray res = "0";
    QObject::connect( &proc, &QProcess::readyReadStandardOutput,
    [&]
    {
        res += proc.readAllStandardOutput();
    });

    auto arr = QJsonDocument(obj).toJson(QJsonDocument::Compact);

    vdeb << "Size of res json arr: " << arr.size();

    auto json_fname = "json.tmp";
    {
        QFile f(json_fname);
        if (!f.open(QIODevice::WriteOnly)) throw verror;
        f.write(arr);
    }
    auto cmd = QString("cat ") + json_fname + "|zlib-flate -compress=9|base64 --wrap=0";

    proc.start( "bash", QStringList{"-c",cmd} );
    proc.waitForFinished();

    return res;
}
//=======================================================================================
