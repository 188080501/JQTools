/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "screenColorPicker.h"
#include <QClipboard>


using namespace ScreenColorPicker;


Manage::Manage(): colorPicker(new ColorPicker),currentColor(QColor("blue"))
{
  connect(colorPicker, &ColorPicker::colorSelect, this,  &Manage::onColorSelect);
}

void Manage::onColorSelect(const QColor & c)
{
  currentColor = c;
  emit colorSelect(c);
}

void Manage::openPicker()
{
  colorPicker->show();
}

void Manage::copyColorToClipboard()
{
  QGuiApplication::clipboard()->setText(currentColor.name());

}
