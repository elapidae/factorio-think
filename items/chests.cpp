#include "chests.h"

#include "qdeb.h"
#include <QJsonArray>

//=======================================================================================
void Chests::Storage::filter( Item item )
{
    auto obj = ref.toObject();
    {
        auto rf_arr = obj["request_filters"].toArray();
        {
            auto rf_obj = rf_arr.at(0).toObject();
            rf_obj["name"] = item.name;
            rf_arr[0] = rf_obj;
        }
        obj["request_filters"] = rf_arr;
    }
    ref = obj;
}
/*
QJsonValue(object, QJsonObject(
{
"connections":{"1":{"green":[{"entity_id":3},{"entity_id":4}]}},
"entity_number":2,
"name":"logistic-chest-storage",
"position":{"x":223.5,"y":139.5},
"request_filters":[{"count":0,"index":1,"name":"medium-electric-pole"}]}
))
*/
//=======================================================================================
