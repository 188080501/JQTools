/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_QTGROUP_PROPERTYMAKER_CPP_PROPERTYMAKER_H_
#define GROUP_QTGROUP_PROPERTYMAKER_CPP_PROPERTYMAKER_H_

// C++ lib import
#include <functional>

// Qt lib import
#include <QMap>

// JQToolsLibrary import
#include <JQToolsLibrary>

#define PROPERTYMAKER_INITIALIZA                                                            \
{                                                                                           \
    qmlRegisterType<PropertyMaker::Manage>("PropertyMaker", 1, 0, "PropertyMakerManage");   \
}

namespace PropertyMaker
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage();

    ~Manage() = default;

public slots:
    QString make(const QString &source, const bool &withSlot, const bool &withInline);

private:
    QMap< QString, std::function< QString( const QString &type, const QString &name, const QString &value, const QString &notifyValue, const bool &withSlot, const bool &withInline ) > > propertyMaker_;
};

}

#endif//GROUP_QTGROUP_PROPERTYMAKER_CPP_PROPERTYMAKER_H_
