/*
    This file is part of JQLibrary

    Copyright: Jason

    Contact email: 188080501@qq.com

    GNU Lesser General Public License Usage
    Alternatively, this file may be used under the terms of the GNU Lesser
    General Public License version 2.1 or version 3 as published by the Free
    Software Foundation and appearing in the file LICENSE.LGPLv21 and
    LICENSE.LGPLv3 included in the packaging of this file. Please review the
    following information to ensure the GNU Lesser General Public License
    requirements will be met: https://www.gnu.org/licenses/lgpl.html and
    http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
*/

#ifndef JQLIBRARY_INCLUDE_JQDECLARE_H_
#define JQLIBRARY_INCLUDE_JQDECLARE_H_

// Macro define
#define PropertyDeclare(Type, name, setName, ...)                                           \
    private:                                                                                \
    Type name ## _ __VA_ARGS__;                                                             \
    public:                                                                                 \
    inline const Type &name() const { return name ## _; }                                   \
    inline void setName(const Type &name) { name ## _ = name; }                             \
    private:

#define PropertyDeclareWithSlot(Type, name, setName, ...)                                   \
    private:                                                                                \
    Type name ## _ __VA_ARGS__;                                                             \
    public Q_SLOTS:                                                                         \
    Type name() const { return name ## _; }                                                 \
    void setName(const Type &name) { name ## _ = name; }                                    \
    private:

#define PtrPropertyDeclare(Type, name, setName, ...)                                        \
    private:                                                                                \
    Type *name ## _ __VA_ARGS__;                                                            \
    public:                                                                                 \
    inline const Type *name() const                                                         \
        { return name ## _; }                                                               \
    inline void setName(const Type &name)                                                   \
        { if ( name ## _ ) { delete name ## _; }                                            \
        name ## _ = new Type( name ); }                                                     \
    private:

#define JQ_READ_AND_SET_PROPERTY( Type, name, setName )                                     \
    public:                                                                                 \
    inline const Type &name() const { return name ## _; }                                   \
    inline void setName(const Type &name) { name ## _ = name; }                             \
    private:

#define JQ_STATIC_READ_AND_SET_PROPERTY( Type, name, setName )                              \
    public:                                                                                 \
    static inline const Type &name() { return name ## _; }                                  \
    static inline void setName(const Type &name) { name ## _ = name; }                      \
    private:

#define JQ_STATIC_SET_PROPERTY( Type, name, setName )                                       \
    public:                                                                                 \
    static inline void setName(const Type &name) { name ## _ = name; }                      \
    private:

#define RUNONOUTRANGEHELPER2( x, y ) x ## y
#define RUNONOUTRANGEHELPER( x, y ) RUNONOUTRANGEHELPER2( x, y )
#define RUNONOUTRANGE( ... )                                                                \
    auto RUNONOUTRANGEHELPER( runOnOutRangeCallback, __LINE__ ) = __VA_ARGS__;              \
    QSharedPointer< int > RUNONOUTRANGEHELPER( runOnOutRange, __LINE__ )(                   \
        new int,                                                                            \
        [ RUNONOUTRANGEHELPER( runOnOutRangeCallback, __LINE__ ) ](int *data)               \
    {                                                                                       \
        RUNONOUTRANGEHELPER( runOnOutRangeCallback, __LINE__ )();                           \
        delete data;                                                                        \
    } );                                                                                    \
    if ( RUNONOUTRANGEHELPER( runOnOutRange, __LINE__ ).data() == nullptr ) { exit( -1 ); }

#define rforeach (variable, container)                                                      \
for (RforeachContainer<__typeof__((container))> _container_((container));                   \
    _container_.__howMuch__; _container_.__howMuch__--)                                     \
    for (variable = *(--_container_.__now__); ; __extension__ ({ break;}))

#define JQCONST( property ) \
    static_cast< const decltype( property ) >( property )

#define JQBUILDDATETIMESTRING                                                                               \
    ( QDateTime(                                                                                            \
        QLocale( QLocale::English ).toDate( QString( __DATE__ ).replace( "  ", " 0" ), "MMM dd yyyy"),      \
        QTime::fromString( __TIME__, "hh:mm:ss" )                                                           \
    ).toString( "yyyy-MM-dd hh:mm:ss" ).toLatin1().data() )

#endif//JQLIBRARY_INCLUDE_JQDECLARE_H_
