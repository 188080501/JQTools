/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_TOOLSGROUP_SCREENCOLORPICKER_CPP_SCREENCOLORPICKER_H
#define GROUP_TOOLSGROUP_SCREENCOLORPICKER_CPP_SCREENCOLORPICKER_H

// Qt lib import
#include <QJsonObject>

// JQToolsLibrary import
#include <JQToolsLibrary>
#include "colorpicker.h"


#define SCREENCOLORPICKER_INITIALIZA                                                              \
{                                                                                               \
    qmlRegisterType<ScreenColorPicker::Manage>("ScreenColorPicker", 1, 0, "ScreenColorPickerManage"); \
}

namespace ScreenColorPicker
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage();
    ~Manage() = default;
signals:
    void colorSelect(const QColor & c);
public slots:
    void openPicker();
    void onColorSelect(const QColor & c);
    void copyColorToClipboard();

private:
    QColor currentColor;
    ColorPicker *colorPicker;
};

}

#endif//GROUP_TOOLSGROUP_SCREENCOLORPICKER_CPP_SCREENCOLORPICKER_H
