/*
    This file is part of JQLibrary

    Copyright: Jason and others

    Contact email: 188080501@qq.com

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef JQLIBRARY_INCLUDE_JQDECLARE_HPP_
#define JQLIBRARY_INCLUDE_JQDECLARE_HPP_

// Macro define
#define JQPROPERTYDECLARE( Type, name, setName, ... )                  \
private:                                                               \
    Type name##_ __VA_ARGS__;                                          \
                                                                       \
public:                                                                \
    inline const Type &name() const { return name##_; }                \
    inline void        setName( const Type &name ) { name##_ = name; } \
                                                                       \
private:

#define JQPROPERTYDECLAREWITHSLOT( Type, name, setName, ... ) \
private:                                                      \
    Type name##_ __VA_ARGS__;                                 \
public Q_SLOTS:                                               \
    Type name() const { return name##_; }                     \
    void setName( const Type &name ) { name##_ = name; }      \
                                                              \
private:

#define JQPTRPROPERTYDECLARE( Type, name, setName, ... ) \
private:                                                 \
    Type *name##_ __VA_ARGS__;                           \
                                                         \
public:                                                  \
    inline const Type *name() const { return name##_; }  \
    inline void        setName( const Type &name )       \
    {                                                    \
        if ( name##_ )                                   \
        {                                                \
            delete name##_;                              \
        }                                                \
        name##_ = new Type( name );                      \
    }                                                    \
                                                         \
private:

#define JQ_READ_AND_SET_PROPERTY( Type, name, setName )                \
public:                                                                \
    inline const Type &name() const { return name##_; }                \
    inline void        setName( const Type &name ) { name##_ = name; } \
                                                                       \
private:

#define JQ_STATIC_READ_AND_SET_PROPERTY( Type, name, setName )                \
public:                                                                       \
    static inline const Type &name() { return name##_; }                      \
    static inline void        setName( const Type &name ) { name##_ = name; } \
                                                                              \
private:

#define JQ_STATIC_SET_PROPERTY( Type, name, setName )                  \
public:                                                                \
    static inline void setName( const Type &name ) { name##_ = name; } \
                                                                       \
private:

#define RUNONOUTRANGEHELPER2( x, y ) x##y
#define RUNONOUTRANGEHELPER( x, y )  RUNONOUTRANGEHELPER2( x, y )
#define RUNONOUTRANGE( ... )                                                                    \
    auto                  RUNONOUTRANGEHELPER( runOnOutRangeCallback, __LINE__ ) = __VA_ARGS__; \
    QSharedPointer< int > RUNONOUTRANGEHELPER( runOnOutRange, __LINE__ )(                       \
        new int,                                                                                \
        [ RUNONOUTRANGEHELPER( runOnOutRangeCallback, __LINE__ ) ]( int *data ) {               \
            RUNONOUTRANGEHELPER( runOnOutRangeCallback, __LINE__ )                              \
            ();                                                                                 \
            delete data;                                                                        \
        } );                                                                                    \
    if ( RUNONOUTRANGEHELPER( runOnOutRange, __LINE__ ).data() == nullptr )                     \
    {                                                                                           \
        exit( -1 );                                                                             \
    }

#define RUNONOUTRANGETIMER( message )                                                            \
    const auto &&runOnOutRangeTimerTime = QDateTime::currentMSecsSinceEpoch();                   \
    RUNONOUTRANGE( [ = ]() {                                                                     \
        qDebug() << message << ( QDateTime::currentMSecsSinceEpoch() - runOnOutRangeTimerTime ); \
    } )

#define JQCONST( property ) static_cast< const decltype( property ) >( property )

#define JQTICKCOUNTERMESSAGE( message )                     \
    {                                                       \
        static JQTickCounter tickCounter;                   \
        tickCounter.tick();                                 \
        qDebug() << message << tickCounter.tickPerSecond(); \
    }

#define JQBUILDDATETIMESTRING                                                                             \
    ( QDateTime(                                                                                          \
          QLocale( QLocale::English ).toDate( QString( __DATE__ ).replace( "  ", " 0" ), "MMM dd yyyy" ), \
          QTime::fromString( __TIME__, "hh:mm:ss" ) )                                                     \
          .toString( "yyyy-MM-dd hh:mm:ss" )                                                              \
          .toLatin1()                                                                                     \
          .data() )

#define JQONLYONCE                    \
    if ( []() {                       \
             static auto flag = true; \
             if ( flag )              \
             {                        \
                 flag = false;        \
                 return true;         \
             }                        \
             return false;            \
         }() )

#define JQSKIPFIRST                   \
    if ( []() {                       \
             static auto flag = true; \
             if ( flag )              \
             {                        \
                 flag = false;        \
                 return false;        \
             }                        \
             return true;             \
         }() )

#define JQINTERVAL( timeInterval )                                            \
    if ( []() {                                                               \
             static qint64 lastTime    = 0;                                   \
             const auto && currentTime = QDateTime::currentMSecsSinceEpoch(); \
             if ( qAbs( currentTime - lastTime ) > timeInterval )             \
             {                                                                \
                 lastTime = currentTime;                                      \
                 return true;                                                 \
             }                                                                \
             return false;                                                    \
         }() )

// Export
#ifdef JQLIBRARY_EXPORT_ENABLE
#    ifdef JQLIBRARY_EXPORT_MODE
#        define JQLIBRARY_EXPORT Q_DECL_EXPORT
#    else
#        define JQLIBRARY_EXPORT Q_DECL_IMPORT
#    endif
#else
#    define JQLIBRARY_EXPORT
#endif

#endif    // JQLIBRARY_INCLUDE_JQDECLARE_HPP_
