#include "parse_lua_recipe.h"

#include <string>
#include "vlog.h"
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>


using namespace std;
using QByteArrayList = QList<QByteArray>;

//=======================================================================================

auto path_to_factorio = QString("../../factorio/");
auto path_to_recipe_lua = path_to_factorio + "/data/base/prototypes/recipe.lua";

//=======================================================================================

QByteArray rm_all_spaces(QByteArray in)
{
    QByteArray res;
    for( auto ch: in )
    {
        switch ( ch )
        case '\n':
        case '\t':
        case ' ':
        case '\r':
            continue;
        res.push_back( ch );
    }
    return res;
}

//=======================================================================================

bool is_letter_or_num( char ch )
{
    bool ok1 = ch >= 'a' && ch <= 'z';
    bool ok2 = ch >= '0' && ch <= '9';
    bool ok3 = ch == '-';
    bool ok4 = ch == '_';
    bool ok5 = ch == '.' || ch == '/';
    bool ok6 = ch == '[' || ch == ']';
    return ok1 || ok2 || ok3 || ok4 || ok5 || ok6;
}

//=======================================================================================

bool is_letter_or_num( QByteArray arr )
{
    for( auto ch: arr )
        if ( !is_letter_or_num(ch) )
            return false;

    return true;
}

//=======================================================================================

QByteArray take_str_token( QByteArray * in )
{
    if ( in->isEmpty() ) throw verror;
    if ( in->front() != '"' ) throw verror;
    in->remove(0,1);

    QByteArray res;
    while( in->front() != '"' )
    {
        res += in->front();
        in->remove(0,1);
    }
    in->remove(0,1);
    return res;
}

//=======================================================================================

QByteArray take_word_token( QByteArray * in )
{
    if ( in->isEmpty() ) throw verror;

    QByteArray res;
    while( is_letter_or_num(in->front()) )
    {
        res += in->front();
        in->remove(0,1);
    }

    if ( res.isEmpty() ) throw verror << *in;

    return res;
}
//=======================================================================================
QByteArray take_token( QByteArray * in )
{
    if ( in->isEmpty() ) throw verror;

    char ch = in->front();

    if ( ch == '{') { in->remove(0,1); return QByteArray() + ch; }
    if ( ch == '}') { in->remove(0,1); return QByteArray() + ch; }
    if ( ch == ',') { in->remove(0,1); return QByteArray() + ch; }
    if ( ch == '=') { in->remove(0,1); return QByteArray() + ch; }

    if ( ch == '"') return take_str_token( in );

    return take_word_token( in );
}

//=======================================================================================

QByteArrayList tokenize( QByteArray in )
{
    QByteArrayList res;
    while( !in.isEmpty() )
    {
        res += take_token( &in );
        //vdeb.nospace() << "taked '" << res.back() << "'";
    }
    return res;
}

//=======================================================================================

QStringList split_by_braces( QString in )
{
    QStringList res;

    if ( in.at(0) != '{' )
    {
        res.push_back( in );
        return res;
    }

    return res;
}

//=======================================================================================

QByteArray rm_comments( QByteArray data )
{
    QByteArray res;
    auto list = data.split('\n');
    for( auto a: list )
    {
        auto str = a.toStdString();
        auto found = str.find( " --" );
        str = str.substr( 0, found );
//        if ( found != string::npos )
//        {
//            vdeb << "Comment deleted: " << a << "\n" << str;
//        }
        res += QByteArray::fromStdString(str);
    }
    return res;
}

//=======================================================================================

struct Token
{
    enum Type { open, close, word, obj, list, equal, semicolon } type;
    int level = 0;
    QByteArray val;
};

using TokenList = QList<Token>;
TokenList token_list( QByteArrayList raw_tokens )
{
    TokenList res;
    int level = 0;
    for( auto &t: raw_tokens )
    {
        if ( t == "{" )
        {
            res.append( {Token::open,++level,t} );
            continue;
        }
        if ( t == "}" )
        {
            res.append( {Token::close,level--,t} );
            continue;
        }
        if ( t == "," )
        {
            res.append( {Token::semicolon,level,t} );
            continue;
        }
        if ( t == "=" )
        {
            res.append( {Token::equal,level,t} );
            continue;
        }
        if ( is_letter_or_num(t) )
        {
            res.append( {Token::word,level,'"' + t + '"'} );
            continue;
        }
        throw verror << t;
    }
    return res;
}

//=======================================================================================
Token decode( TokenList tokens )
{
   // for(auto token: tokens)
     //   vdeb << token.level << token.val;

    //  open close
    tokens.removeFirst();
    tokens.removeLast();

    if ( tokens.size() == 1 )
    {
        auto c = tokens.first();
        if ( c.type != Token::obj && c.type != Token::list )
            throw verror << c.val << c.type;

        return c;
    }

    auto second = tokens.at(1);

    //  We are list
    if ( second.type == Token::semicolon )
    {
        QByteArray list;
        for ( int i = 0; i < tokens.size(); i+=2 )
        {
            auto cur = tokens.at(i);
            list += cur.val;
            if ( i+1 < tokens.size() )
            {
                auto next = tokens.at(i+1);
                if ( next.type != Token::semicolon ) throw verror << next.val;
                list += ",";
            }
        }
        return { Token::list, tokens.first().level, '[' + list + ']' };
    }

    if ( second.type == Token::equal )
    {
        QByteArray obj;
        for ( int i = 0; i < tokens.size(); i+=4 )
        {
            auto c0 = tokens.at(i);
            auto c1 = tokens.at(i+1);
            auto c2 = tokens.at(i+2);

            if ( c1.type != Token::equal ) throw verror << c1.val;
            obj += c0.val + ":" + c2.val;
            if ( i+3 < tokens.size() )
            {
                auto c3 = tokens.at(i+3);
                if ( c3.type != Token::semicolon ) throw verror << c3.val;
                if ( i+4 < tokens.size() )
                    obj += ",";
            }
        }
        return { Token::obj, tokens.first().level, '{' + obj + '}' };
    }

    vdeb << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    for(auto token: tokens)
        vdeb << token.level << token.val;

    exit(1);
}
//=======================================================================================
bool join( const TokenList& tokens, TokenList& res )
{
    int last_open_index = -1;

    for ( int i = 0; i < tokens.size(); ++i )
    {
        auto cur = tokens.at(i);
        if ( cur.type == Token::open )
        {
            last_open_index = i;
            res.append( cur );
            continue;
        }
        if ( cur.type != Token::close )
        {
            res.append( cur );
            continue;
        }

        while( res.size() > last_open_index )
        {
            //vdeb << "delete from res" << res.last().val;
            res.removeLast();
        }

        TokenList dec;
        for(int j = last_open_index; j <= i; ++j)
            dec.append( tokens.at(j) );

        auto d = decode(dec);

        //vdeb << "decoded" << d.val;
        res.append( d );


        for( int j = i+1; j < tokens.size(); ++j )
            res.append( tokens.at(j));

        return true;
    }
    return false;
}

//=======================================================================================

QJsonArray parse_lua_recipe::recipe()
{
    QFile f( path_to_recipe_lua );
    if( !f.open(QIODevice::ReadOnly) ) throw verror;

    auto array = rm_comments( f.readAll() );
    array = rm_all_spaces( array );

    QByteArray data_extend = "data:extend(";
    if ( !array.startsWith(data_extend) ) throw verror;
    array.remove( 0, data_extend.size() );
    if ( !array.endsWith(")") ) throw verror;
    array.remove( array.size() - 1, 1 );

    auto tokens = token_list( tokenize(array) );

    TokenList tokens2;
    while( join(tokens, tokens2) )
    {
        tokens = tokens2;
        tokens2.clear();
    }

    //vdeb << "TOKENS2 SIZE:" << tokens2.size();
    if ( tokens2.size() != 1 ) throw verror << tokens2.size();

    QJsonParseError err;
    auto json = QJsonDocument::fromJson( tokens2.first().val, &err );
    if ( err.error != QJsonParseError::NoError )
        throw verror << err.errorString() << "  " << err.offset;

    //vdeb << json.isArray() << json.isObject();
    //qDebug() << json.array();
    return json.array();
}

//=======================================================================================

QJsonValue extract( QJsonObject& o, QString key )
{
    if ( !o.contains(key) ) throw verror << "Has not " << key;
    return o.take( key );
}

//=======================================================================================

auto skip_recipes = []
{
    QSet<QString> res;

    res.insert( "basic-oil-processing" );
    res.insert( "advanced-oil-processing" );
    res.insert( "coal-liquefaction" );
    res.insert( "heavy-oil-cracking" );
    res.insert( "light-oil-cracking" );
    res.insert( "sulfuric-acid" );
    res.insert( "plastic-bar" );
    res.insert( "solid-fuel-from-light-oil" );
    res.insert( "solid-fuel-from-petroleum-gas" );
    res.insert( "solid-fuel-from-heavy-oil" );
    res.insert( "sulfur" );
    res.insert( "lubricant" );
    res.insert( "discharge-defense-remote" );
    res.insert( "steam-engine" );
    //res.insert( "" );
    //res.insert( "" );
    //res.insert( "" );
    //res.insert( "" );
    //res.insert( "" );
    //res.insert( "" );
    //res.insert( "" );
    //res.insert( "" );
    //res.insert( "" );
    //res.insert( "" );
    //res.insert( "" );
    //res.insert( "" );
    //=================================
    //res.insert( "" );
    //res.insert( "" );
    //res.insert( "" );
    res.insert( "rocket-fuel" );
    res.insert( "battery" );
    res.insert( "explosives" );
    res.insert( "electric-engine-unit" );
    res.insert( "processing-unit" );
    res.insert( "express-splitter" );
    res.insert( "express-underground-belt" );
    res.insert( "express-transport-belt" );
    res.insert( "flamethrower-ammo" );
    res.insert( "refined-concrete" );
    res.insert( "concrete" );
    res.insert( "wooden-chest" );
    res.insert( "empty-barrel" );
    return res;
}();

static bool skip_recipe(QString name)
{
    return skip_recipes.contains(name);
}
//=======================================================================================

Recipe::List parse_lua_recipe::interpret()
{
    auto arr = recipe();

    Recipe::List res;

    for ( auto item: arr )
    {
        auto obj = item.toObject();
        if ( obj.isEmpty() ) throw verror;

        if ( obj.keys().contains("normal") )
        {
            auto norm = obj["normal"].toObject();
            obj["ingredients"] = norm["ingredients"];
            obj["result"]      = norm["result"];
        }

        Recipe cur;
        cur.name = extract(obj, "name").toString();
        if ( skip_recipe(cur.name) ) continue;

        auto result = obj["result"].toString();
        if ( result.isEmpty() || result != cur.name )
            vwarning << "Result strange:" << result << ", name:" << cur.name;

        cur.prod_time = obj["energy_required"].toString().toInt();

        cur.count = obj.contains("result_count")
                        ? obj["result_count"].toString().toInt()
                        : 1;

        //qDebug() << obj;
        auto v_ingrs = extract(obj, "ingredients");
        if ( !v_ingrs.isArray() )
        {
            vdeb << cur.name;
            qDebug() << v_ingrs;
            throw verror;
        }
        auto ingrs = v_ingrs.toArray();
        if( ingrs.isEmpty()) throw verror;

        //  Only one record as recipe
        if ( ingrs.size() == 2 && ingrs.at(1).toString().toInt() != 0 )
        {
            ingrs = QJsonArray() << (QJsonArray() << ingrs.at(0) << ingrs.at(1));
        }
        for( auto in: ingrs )
        {
            if ( !in.isArray() )
            {
                qDebug() << "====================";
                qDebug() << in;
                qDebug() << "====================";
                qDebug() << ingrs << ingrs.size() << ingrs.at(1).toString().toInt();
                qDebug() << "====================";
                vdeb << in.type() << cur.name;
                throw verror;
            }
            auto l = in.toArray(); if (l.size() != 2) throw verror;

            Recipe i;
            i.name = l.at(0).toString();
            i.count = l.at(1).toInt();
            cur.ingredients.insert( i.name, i );

        } //each ingredient

        //static auto cnt = 0;
        //vdeb << cur.name << ++cnt << "OK";
        res.append( cur );
        //qDebug() << obj;

        //return;
    }
    return res;
}

//=======================================================================================

