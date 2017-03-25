/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef __GROUP_MAKEGROUP_QRCODEMAKER_CPP_QRCODEMAKER_H__
#define __GROUP_MAKEGROUP_QRCODEMAKER_CPP_QRCODEMAKER_H__

// Qt lib import
#include <QImage>

// JQToolsLibrary import
#include "JQToolsLibrary.h"

#define QRCODEMAKER_INITIALIZA                                                          \
{                                                                                       \
    qmlRegisterType< QRCodeMaker::Manage >( "QRCodeMaker", 1, 0, "QRCodeMakerManage" ); \
}

namespace QRCodeMaker
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage();

    ~Manage() = default;
};

}

#endif//__GROUP_MAKEGROUP_QRCODEMAKER_CPP_QRCODEMAKER_H__
