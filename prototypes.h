#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <QJsonArray>
#include <QJsonObject>

class Prototypes
{
public:
    Prototypes();

    int api_version = 0;
    QString application_version;

    QJsonArray prototypes;
    QJsonArray types;
};

#endif // PROTOTYPES_H
