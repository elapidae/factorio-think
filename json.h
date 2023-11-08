#pragma once

#include <QJsonObject>
#include <QJsonArray>

//=======================================================================================
class JsonObject : public QJsonObject
{
    void find_set( const QString& key1, const QJsonValue &val );
    void find_set( const QString& key1, const QString& key2, const QJsonValue &val );
};
//=======================================================================================
namespace Json
{
    QJsonObject get_obj( const QJsonObject& obj, const QString& key );
    void replace_val( QJsonObject *obj, const QString &key, const QJsonValue &val );

    void find_set( QJsonObject* obj, const QJsonValue& val,
                   const QString& key1 );

    void find_set( QJsonObject* obj, const QJsonValue& val,
                   const QString& key1,
                   const QString& key2 );

    void find_set( QJsonObject* obj, const QJsonValue& val,
                   const QString& key1,
                   const QString& key2,
                   const QString& key3 );
}
//=======================================================================================
