#pragma once

#include "vlog.h"
#include <QDebug>
#define qdeb qDebug() << QByteArray::fromStdString(V_POSITION_FIX.place())
