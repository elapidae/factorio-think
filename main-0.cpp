#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>

#include "vlog.h"

//https://github.com/kevinta893/factorio-recipes-json

QPdfWriter * pdf     {nullptr};
QPainter   * painter {nullptr};
int page = 0;
void tune_pdf()
{
    delete painter;
    delete pdf;

    pdf = new QPdfWriter( QString("../factorio-think/out_%1.pdf").arg(page++) );
    painter = new QPainter( pdf );

    painter->setFont( QFont("Arial",13) );

    pdf->setResolution(254);
    vdeb << pdf->resolution();

    pdf->setPageSize( QPageSize(QPageSize::A4) );
    pdf->setPageMargins( QMarginsF(20, 20, 20, 20), QPageLayout::Millimeter );

    painter->scale( 3, 3 );
    painter->translate( 30, 30 );
}

int row = 0;
int col = 0;

void print_one( const QJsonObject& obj )
{
    qreal y_shift = 0;

    auto font_name = "Courier New";
    //auto font_name = "";

    auto id   = obj["id"].toString();
    auto name = obj["name"].toString();
    auto type = obj["type"].toString();
    auto category = obj["category"].toString();

    if ( !obj["recipe"].isObject() ) throw verror;
    auto recipe = obj["recipe"].toObject();
    auto time        = recipe["time"].toDouble();
    auto yield       = recipe["yield"].toInt();
    auto ingredients = recipe["ingredients"].toArray();
    if ( ingredients.isEmpty() ) vwarning << name << "Has not ingredients";

    auto y_indent = 80;
    auto y_pos = 40;

    auto font = QFont( font_name, 17 );
    font.setBold( true );
    painter->setFont( font );

    QRectF rect( 0, 0, 2000, 300 );
    //painter->drawText( 0, y_pos, name );
    painter->drawText( rect, name );
    painter->translate( 0, y_indent );
    y_shift += y_indent;

    font = QFont( font_name, 14 );
    font.setBold( false );
    painter->setFont( font );
    painter->drawText( 0, y_pos, category + " / " + type );

    painter->translate( 0, y_indent );
    y_shift += y_indent;
    painter->drawText( 0, y_pos, QString("%1 sec, %2 pcs").arg(time).arg(yield) );
    painter->translate( 0, y_indent * 1.3 );
    y_shift += y_indent * 1.3;

    font = QFont( font_name, 15 );
    font.setItalic( true );
    font.setBold( true );
    painter->setFont( font );

    auto ing_count = 0;
    for ( auto v: ingredients )
    {
        ++ing_count;
        if ( !v.isObject() ) throw verror;
        auto o = v.toObject();
        auto id = o["id"].toString();
        auto amount = o["amount"].toDouble();

        painter->drawText( 100, y_pos, QString("%1: %2").arg(id).arg(amount) );
        painter->translate( 0, y_indent );
        y_shift += y_indent;
    }
    while( ing_count++ < 5 )
    {
        painter->drawText( 100, y_pos, "--" );
        painter->translate( 0, y_indent );
        y_shift += y_indent;
    }

    //vdeb << y_shift + 2 * y_indent; // 584

    const auto x_indent = 1090;
    const auto y_rect   = y_indent * 9;

    auto pen = painter->pen();
    painter->setPen( QPen() );
    painter->drawRect( -70, 0, x_indent, -y_rect );
    painter->setPen( pen );


    if ( ++col == 3 )
    {
        col = 0;
        auto y = y_rect - y_shift;
        painter->translate( -x_indent*2, y );
        if ( ++row == 6 )
        {
            row = 0;
            tune_pdf();
        }
    }
    else
    {
        painter->translate( x_indent, -y_shift );
    }
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    tune_pdf();

    QFile f( "../factorio-think/factorio-recipes-json/recipes.json" );
    if (!f.open(QIODevice::ReadOnly) )
        throw verror << "open";

    QJsonParseError error;
    auto doc = QJsonDocument::fromJson( f.readAll(), &error );

    if ( error.error != QJsonParseError::NoError ) throw verror << error.errorString();

    if ( !doc.isArray() ) throw verror;

    auto array = doc.array();

    int cnt = 0;
    for ( auto val: array )
    {
        if ( !val.isObject() ) throw verror;
        print_one( val.toObject() );

       // if (++cnt == 4) break;
    } // for all entries

    delete painter;
    delete pdf;
    return 0;
}
