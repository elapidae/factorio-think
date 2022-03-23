#include "blue.h"

#include <QByteArray>
#include "vlog.h"
#include <QDataStream>
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>

auto raw =
R"(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)";

auto raw2 =
R"(0eNpljtsOgyAYg9+l18zMiUF5lWVZPPxZ2AQJ4DJjePeB3izZZZv2azf000LWKRMgN6hhNh7yusGrh+mm7IXVEiRUIA0G0+ms7KLtsxteiAzKjPSBLOONgUxQQdHB2MV6N4vuyaXAf5vBzj4VZpOXEuTU8KqoGVbItuJFnfCjcjQcEZ4n9iPy5zfDm5zfA5em5KK9iEqIujzzGL8VlUil)";


//9 базовых станций по чанкам.
//+ 4 угловых радара.
//C постройкой на воде!

auto raw3 =
R"(0eNqdnOFuo0gQhN+F33hFz9AM7VdZRSc74XxIDrYIji5a+d0Pxyabi4fsfPyKHBXF0NVdM3Q7+ZVt96fm2LfdkK1/ZS/d5rgaDqtd3z5dPv+bra3Ks7fLj3OebbYvh/1paFYX3LHtdtl66E9Nnh0PL+3QHrpV3+w3Q/vafCFZyZVFLizt46F7ydY/x9u1u26zv2CGt2OTrbN2aJ6zPOs2z5dP/WF7OB76Ibtc1D01I5Gc88hlr20/nMbffFx5Razs05UueuX/b7jfdE9/t/v9p8v8+SHPmm4YH6+5Lvr9w9tf3el52/Tjin4vd/O06bPfwfh49h/6/vCr4oeeL6v4wuA+GLbtbtXsm8ehbx9Xx8O+uWeTK9UYh6xr2t0/28Opv6zL5+IfIuSekDudYXd5GSMvCXlps0vXXKL8SviDn+Ev8xAjr/4knJV/EC6Q5VmYWd748BpbX/3Bvjt1q+HU980Qy653Whdbn91X0r3k85dLkXC9Ft8QSNIjmH5D4RLWYPU3BJ5Xl/P3+S9VTCNZUgH39GUudZReF2TYPX3IXRGlr3hsyvCVfYywjHeIFrCEBfYTuUU1F6B6Qfwj/OXlEcRyF61EsQU+FLlLPaODKxbIHOHX90eIJqqTZC/QIrpJuXQzmGHw6aU8w1DyfA0SSSYXTSanC5Ipwl/nPi5ztUDme/4xW3x0q3ch+ShiOnMUqXmETe9WWObOoiu0BXYQ4Z+LsC8WKBjh13H9uZfoLWSBF9zfws+J6F3ysWRORO8X5FkkCtVcCEpyMrE6ukZN9qMZgirdj2YYAjmdzHDU6Z52YRjfJYZ2f3uR+Bqv2/nVnWPvI7NwQfACoa1kcGXwKhHuWGAcC4xDgbmiGTdbeHLQHQu6WxJ0CwxeJ8KFSSpMUkGSCpJUkKTCJBUmqTBJhUkqSNICKVogQQuiZ0HkLIiaV7BHzIjaIe6yQuiA0Ej10ghakZCKlAyIOyDu1CouUBEXqIYLVMLFggq2RC2ZgzMDR/6N7Bu5t5B6F1TvgupdUL0LqndB9S6o3gXVu6B6F1Tvguqd7dps02Z7Ntuy2Y4tqN7RMRmdktEh2ZGadCi3Hcpth3LbodxmR3V2UmcHdYdyBL1jepIjnuSIJzniUY54lCMe5YhHOcLeoT3KEY9yxDMfKdHBYYILgqdulRM8IHjqxjDBE3eGafrqGFwQPDkyyiKjLDKKIlPWKDITXBC8QGjGzRbuGTcjd4w9NV8meGDwmsENwZVJqkzTwNgDY0+tpAnOKsmYqsZUNaZq6s4xfYHEMbggeIHQjJst3DNuRu4Ye7ILGHMBYy5gzAWMuYAxFzDmAsZcwJgLGHMBYy5gzAWMuYAhF1DUDFbUDVbUDlbUD1bWWFXWWVXWWlXWW1XWpFTWpVTWplTWp1TUTFTUTVTUTlTUT1TWmFPWmVPWmlPWm1PW5FLW5VLW5lLW5wps2hzYtPkGT91PJ3hA8NRdI7AJcmBfUAjsCwrT1+YqBg8InhwZ9oUGY5ExFhlDbTVjT2qLnjS1so01e4w1e27wAqEZN1t4ctBZY2iCs6Cn2ukET7RTY10qY12qG7xAaMbNFp4sKetoTfCKwQODp0paMUkrJmmFJK2QpBWStCIHsImbkTvGnrrdTfDA4CwBUg+PN7gySZVpGhh7YOzJZV2xsq5YWVesrKslZZ168J3+QMkxuCB4gdCMmy3cM25G7hh7sgsE5gKBuUBgLhCYCwTmAoG5QGAuEJgLBOYCgblAYC4QmAsE5gJoGGZoGGZoGGZoGGZsoGRsoGRsoGRsoGRsKGNsKGNsKGNsKGNobGJobGJobGJobGJs9GBs9GBs9GBs9GCsfW+sfW+sfW/fte8f8utf2K8//ZuBPHtt+pd3AldLGcwFX5Vl4d35/B+sDYvT)";

blue::blue()
{
    QByteArray arr( raw3 );
    if ( arr.at(0) != '0' ) throw verror;
    arr.remove(0,1);
    //vdeb << arr;

    auto zipped = arr.fromBase64Encoding( arr );
    if ( !zipped ) throw verror;

    QString cmd = "echo \"" + arr + "\"|base64 -d|zlib-flate -uncompress";
    //system( cmd.data() );
    //return;

    //vdeb << zipped.decoded.toHex();
    QObject::connect( &proc, &QProcess::errorOccurred,
    [&](QProcess::ProcessError error){
        vdeb << "err" << error;
    });
    QByteArray doc;
    QObject::connect( &proc, &QProcess::readyReadStandardOutput,
    [&]{
        doc += proc.readAllStandardOutput();
    });
    proc.start( "bash", QStringList{"-c",cmd} );
    proc.waitForFinished();

    auto json = QJsonDocument::fromJson(doc);
    vdeb << json.toJson();
    exit(0);
    //auto json = qUncompress( zipped.decoded );
    //if (json.isEmpty() ) throw verror;

    //vdeb << json;
}
