#include "json.h"

#include "vlog.h"

//=======================================================================================
//void JsonObject::find_set( const QString& key1,
//                           const QJsonValue& val )
//{
//}
//=======================================================================================
//void JsonObject::find_set( const QString& key1,
//                           const QString& key2,
//                           const QJsonValue& val )
//{
//}
//=======================================================================================


//=======================================================================================
QJsonObject Json::get_obj( const QJsonObject& obj, const QString& key )
{
    if ( !obj.contains(key) ) throw verror;
    return obj[key].toObject();
}
//=======================================================================================
void Json::replace_val( QJsonObject *obj, const QString &key, const QJsonValue &val )
{
    if ( !obj->contains(key) ) throw verror;
    (*obj)[key] = val;
}
//=======================================================================================
void Json::find_set( QJsonObject* obj, const QJsonValue& val,
                     const QString& key1 )
{
    if ( !obj->contains(key1) ) throw verror;
    *obj->find(key1) = val;
}
//=======================================================================================
void Json::find_set( QJsonObject* obj, const QJsonValue& val,
                     const QString& key1,
                     const QString& key2 )
{
    if ( !obj->contains(key1) ) throw verror;
    auto it1 = obj->find( key1 );

    auto o2 = it1->toObject();
    if ( !o2.contains(key2) ) throw verror;
    *o2.find(key2) = val;

    it1.value() = o2;
}
//=======================================================================================
void Json::find_set( QJsonObject* obj, const QJsonValue& val,
                     const QString& key0,
                     const QString& key1,
                     const QString& key2 )
{
    auto o1 = get_obj( *obj, key0 );
    auto o2 = get_obj( o1, key1 );
    replace_val( &o2, key2, val );
    o1[key1] = o2;
    (*obj)[key0] = o1;
}
//=======================================================================================


